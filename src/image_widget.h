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

namespace minmd
{
	class image_widget : public Gtk::Image
	{
		public:
			explicit image_widget(const std::string& path);
			[[nodiscard]] const std::string& get_path() const;
			static void set_config(const minmd::config& t_config);
			static const minmd::config& get_config();
		private:
			std::string m_path;
			static const minmd::config* m_config;
	};
} //namespace minmd
