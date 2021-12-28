#include "config.h"
#include "file_handling.h"
#include "image_widget.h"
#include "main_scrolled_window.h"
#include "main_label.h"
#include "main_window.h"
#include "parse.h"

#include <cstdlib>
#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

int main(int argc, char *argv[])
{
	//zpracovani config souboru
	char * config_dir_p = std::getenv("XDG_CONFIG_HOME"); //NOLINT
	std::string config_dir{}; 
	std::string config_path{};
	if (config_dir_p == nullptr)
	{
		config_dir = std::string(std::getenv("HOME")) + "/.config/minmd/";
	}
	else
	{
		config_dir = std::string(config_dir_p) + "/minmd/";
	}
	config_path = config_dir + "minmd.conf";

	std::string config_source;
	//vytvoreni config objektu
	try	
	{
		config_source = minmd::parse_file(config_path);
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << "\n";
		std::cerr << "Error occured when processing the configuration file. Default configuration will be used." << std::endl;
	};

	const minmd::config current_config(config_source);
	minmd::main_label::set_config(current_config);

	//vytvoreni aplikace ve ktere pobezi program
	int fake_argc = 1;
	auto main_application = Gtk::Application::create(fake_argc, argv, "minmd.main");

	//vytvoreni okna
	main_window window(current_config);

	//vytvoreni ramu pro text
	Gtk::VBox grid;
	grid.set_size_request(current_config.get_value_int("window_width"));
	grid.set_spacing(current_config.get_value_int("row_spacing"));
	grid.set_halign(Gtk::ALIGN_CENTER);
	grid.get_style_context()->add_class("page");

	window.scrolled_window.add(grid);

	//nacteni vstupniho textu + vytvoreni widgetu
	std::string input_text{};

	//test argumentu
	if (argc < 2)
	{
		//standard input
		std::string temp_line;
		while (std::getline(std::cin, temp_line))
		{
			input_text += temp_line + "\n";
		}
	}
	else
	{
		//nacteni ze souboru
		try
		{
			input_text = minmd::parse_file(argv[1]);
		}
		catch (std::runtime_error& e)
		{
			std::cerr << e.what() << std::endl;
			abort();
		};
	}

	minmd::parser main_parser(MD_FLAG_STRIKETHROUGH);
	main_parser.parse(input_text);
	auto& widgets = main_parser.get_widgets();
	auto& images = main_parser.get_images();

	//pridani labelu do gridu
	for (auto& w : widgets)
	{
		grid.pack_start(*w, Gtk::PACK_SHRINK);
	}

	auto resize_images = [&images, &current_config]()
	{
		int desired_width = current_config.get_value_int("window_width");
		for (auto* i : images)	
		{
			i->resize_to_fit(desired_width);
		}
	};

	window.signal_realize().connect(resize_images);

	//zobrazeni vsech prvku v okne
	window.show_all_children();

	//css
	auto css_provider = Gtk::CssProvider::create();
	try
	{
		css_provider->load_from_path(config_dir + "theme.css");
	}
	catch (...)
	{
		throw std::runtime_error("'theme.css' file was not found.");
	}
	auto style_context = Gtk::StyleContext::create();
	auto screen = Gdk::Screen::get_default();
	style_context->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	//spusteni programu
	return main_application->run(window);
}
