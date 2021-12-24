#include "config.h"
#include "file_handling.h"
#include "image_widget.h"
#include "main_scrolled_window.h"
#include "main_grid.h"
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

//void resize_images(Gtk::Allocation alloc, std::vector<Gtk::Widget*>& widgets);
void resize_images(const std::vector<std::unique_ptr<Gtk::Widget>> * widgets, const minmd::config * conf);

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

	//vytvoreni config objektu
	const minmd::config current_config(minmd::parse_file(config_path));
	minmd::main_label::set_config(current_config);

	//vytvoreni aplikace ve ktere pobezi program
	int fake_argc = 1;
	auto main_application = Gtk::Application::create(fake_argc, argv, "minmd.main");

	//vytvoreni okna
	main_window window(current_config);


	//vytvoreni ramu pro text
	//main_grid grid(current_config);
	Gtk::VBox grid;
	grid.set_spacing(current_config.get_value_int("row_spacing"));
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
		input_text = minmd::parse_file(argv[1]);
	}

	std::vector<std::unique_ptr<Gtk::Widget>> widgets = minmd::parse(input_text);

	//pridani labelu do gridu
	/*
	if (!widgets.empty())
	{
		grid.add(*widgets[0]);
		for (auto i = widgets.begin() + 1; i != widgets.end(); i++)
		{
			grid.attach_next_to(**i, **(i - 1), Gtk::POS_BOTTOM);
		}
	}
	*/
	for (auto& w : widgets)
	{
		grid.pack_end(*w);
	}

	//window.signal_size_allocate().connect(sigc::bind(sigc::ptr_fun(resize_images), widgets));
	window.signal_realize().connect(sigc::bind(sigc::ptr_fun(resize_images), &widgets, &current_config));

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

void resize_images(const std::vector<std::unique_ptr<Gtk::Widget>>* widgets, const minmd::config * conf)
{
	for (auto& w : *widgets)
	{
		auto* image = dynamic_cast<image_widget*>(w.get());
		if (image == nullptr)
		{
			continue;
		}

		int window_width = conf->get_value_int("window_width");
		if (image->get_allocated_width() > window_width)
		{
			auto new_pixbuf = Gdk::Pixbuf::create_from_file(image->get_path(), window_width, -1);
			image->set(new_pixbuf);
		}
	}
}
