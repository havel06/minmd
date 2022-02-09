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

#include <string>
#include <unordered_map>

namespace minmd
{
	class config
	{
	public:
		config() noexcept = default;
		explicit config(const std::string& config_source);
		config(const minmd::config& other) = default;
		config(minmd::config&& other) = default;
		config& operator=(const config& other) = default;
		config& operator=(minmd::config&& other) = default;
		~config() = default;

		[[nodiscard]] const std::string& get_value_string(const std::string& key) const;
		[[nodiscard]] int get_value_int(const std::string& key) const;
		[[nodiscard]] float get_value_float(const std::string& key) const;
	private:
		std::unordered_map<std::string, std::string> config_values = {
			{"widget_spacing", "20"},
			{"window_width", "800"},
			{"window_height", "600"},
			{"indent_size", "20"},
			{"vim_scroll_distance", "30"},
			{"vim_long_scroll_distance", "300"},
			{"text_selectable", "0"}
		};
	};
} //namespace minmd
