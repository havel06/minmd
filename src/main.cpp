#include "file_handling.h"
#include "initialize.h"
#include "main_label.h"
#include "main_window.h"
#include "parse.h"



int main(int argc, char *argv[])
{
	std::string config_dir = minmd::get_config_dir();

	minmd::config current_config = minmd::init_config(config_dir + "minmd.conf");
	minmd::main_label::set_config(current_config);

	int fake_argc = 1;
	auto main_application = Gtk::Application::create(fake_argc, argv, "minmd.main");

	std::string input_text = minmd::get_input(argc, argv);

	minmd::parser main_parser(MD_FLAG_STRIKETHROUGH);
	main_parser.parse(input_text);
	const auto& widgets = main_parser.get_widgets();
	const auto& images = main_parser.get_images();

	//vytvoreni okna
	minmd::main_window window(current_config);
	window.display_widgets(widgets, images);

	minmd::init_css(config_dir + "theme.css");

	return main_application->run(window);
}
