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

#pragma once

#include "config.h"
#include <gtkmm.h>
#include <string>

namespace minmd
{
	struct file_input
	{
		std::string contents;
		std::optional<std::string> path;
	};

	void init_css(const std::string& t_css_path);
	[[nodiscard]] std::string get_config_dir();
	[[nodiscard]] minmd::config init_config(const std::string& t_path);
	[[nodiscard]] file_input get_input(int argc, char* argv[]);
} // namespace minmd
