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

#include <gtkmm-3.0/gtkmm.h>
#include <string>

namespace minmd
{
	class main_label : public Gtk::Label
	{
		public:
			main_label(std::string_view markup, unsigned int indent, std::string_view css_class);
			main_label(const main_label& other) = delete;
			main_label& operator=(const main_label& other) = delete;
			main_label(main_label&& other) = delete;
			main_label& operator=(main_label&& other) = delete;
			~main_label() override = default;

			static const minmd::config& get_config();
			static void set_config(const minmd::config& t_config);

		private:
			const std::string markup_src;
			static const minmd::config* m_config;
	};
} //namespace minmd
