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

#include "initialize.h"
#include "file_handling.h"
#include <gtkmm.h>
#include <iostream>

inline const std::string default_css = R"(
window
{
	background-color: #22272e;
	color: #adbac7;
	font-size: 16px;
}
.page
{
	border: 1px solid #444c56;
	border-radius: 0.375em;
	padding-top: 1em;
	padding-right: 2em;
	padding-left: 2em;
	padding-bottom: 2em;
}
statusbar
{
	border-top: 1px solid #444c56;
}
.heading1
{
	font-size: 2em;
	font-weight: bold;
	padding-bottom: 0.3em;
	border-bottom: 1px solid #373e47;
}
.heading2
{
	font-size: 1.5em;
	font-weight: bold;
	padding-bottom: 0.3em;
	border-bottom: 1px solid #373e47;
}
.heading3
{
	font-size: 1.25em;
	font-weight: bold;
}
.heading4
{
	font-size: 1em;
	font-weight: bold;
}
.heading5
{
	font-size: 0.875em;
	font-weight: bold;
}
.heading6
{
	font-size: 0.85em;
	font-weight: bold;
}

.quote
{
	color: #768390;
	border-left: 4px solid #444c56;
	padding-left: 1em;
}

.code
{
	font-family: monospace;	
	background-color: #2d333b;
	padding: 1em;
	border-radius: 0.375em;
	font-size: 0.85em;
}
	)";



void minmd::init_css(const std::string& t_css_path)
{
	auto css_provider = Gtk::CssProvider::create();
	try
	{
		css_provider->load_from_path(t_css_path);
	}
	catch (...)
	{
		std::cerr << "Warning: Error occured when processing stylesheet. Default stylesheet will be used." << std::endl;
		css_provider->load_from_data(default_css);
	}
	auto style_context = Gtk::StyleContext::create();
	auto screen = Gdk::Screen::get_default();
	style_context->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}




std::string minmd::get_config_dir()
{
	char * config_dir_p = std::getenv("XDG_CONFIG_HOME"); //NOLINT
	if (config_dir_p == nullptr)
	{
		return std::string(std::getenv("HOME")) + "/.config/minmd/";
	}
	return std::string(config_dir_p) + "/minmd/";
}




minmd::config minmd::init_config(const std::string& t_path)
{
	try	
	{
		auto config_source = minmd::parse_file(t_path);
		return minmd::config(config_source);
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << "\n";
		std::cerr << "Error occured when processing the configuration file. Default configuration will be used." << std::endl;
		return minmd::config();
	};
}




std::string minmd::get_input(int argc, char* argv[])
{
	std::string input_text{};

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
	return input_text;
}
