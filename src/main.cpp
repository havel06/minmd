/*
 * Copyright (c) 2021-2022 Michal Havlíček
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

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
	minmd::image_widget::set_config(current_config);

	int fake_argc = 1;
	auto main_application = Gtk::Application::create(fake_argc, argv, "minmd.main");

	auto [input_text, path] = minmd::get_input(argc, argv);

	minmd::main_window window(current_config);
	minmd::parser main_parser(MD_FLAG_STRIKETHROUGH);

	auto on_file_modify = [&main_parser, &window](const std::string& t_input ){
		main_parser.clear_widgets();
		main_parser.parse(t_input);
		const auto& widgets = main_parser.get_widgets();
		window.display_widgets(widgets);
	};

	// first creation of widgets
	on_file_modify(input_text);

	if (path.has_value())
	{
		window.set_file_watcher(*path, [path = path, on_file_modify](){
			on_file_modify(minmd::parse_file(*path));
		});
	}

	minmd::init_css(config_dir + "theme.css");

	return main_application->run(window);
}
