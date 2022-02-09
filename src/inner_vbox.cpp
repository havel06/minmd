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

#include "inner_vbox.h"

namespace minmd
{
	inner_vbox::inner_vbox(const minmd::config& t_config)
	{
		this->set_size_request(t_config.get_value_int("window_width"));
		this->set_spacing(t_config.get_value_int("widget_spacing"));
		this->set_halign(Gtk::ALIGN_CENTER);
		this->get_style_context()->add_class("page");
	}
} //namespace minmd
