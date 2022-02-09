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

#include "image_widget.h"
#include <iostream>

namespace minmd
{
	image_widget::image_widget(const std::string& path)
	{
		auto pixbuf = Gdk::Pixbuf::create_from_file(path);

		int width = this->get_config().get_value_int("window_width");
		if (pixbuf->get_width() > width)
		{
			auto new_pixbuf = Gdk::Pixbuf::create_from_file(path, static_cast<int>(width), -1, true);
			this->set(new_pixbuf);
		}
		else
		{
			this->set(pixbuf);
		}

		this->m_path = path;	
	}

	const std::string& image_widget::get_path() const
	{
		return this->m_path;
	}


	const minmd::config*image_widget::m_config = nullptr;

	void image_widget::set_config(const minmd::config& t_config)
	{
		image_widget::m_config = &t_config;
	}


	const minmd::config& image_widget::get_config()
	{
		return *image_widget::m_config;
	}

} //namespace minmd
