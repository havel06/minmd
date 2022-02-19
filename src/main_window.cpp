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

#include "main_window.h"
#include <cmath>
#include <sys/inotify.h>
#include <iostream>

namespace minmd
{
	main_window::main_window(const minmd::config& conf) : m_outer_vbox(Gtk::ORIENTATION_VERTICAL), m_scrolled_window(conf),
	m_inner_vbox(conf), current_config(conf)
	{
		this->set_title("testing window");
		this->set_size_request(this->current_config.get_value_int("window_width"),
				this->current_config.get_value_int("window_height"));
		this->set_border_width(0);

		this->add(m_outer_vbox);
		m_outer_vbox.pack_start(m_scrolled_window);
		m_outer_vbox.pack_end(m_status_bar, false, false);
		m_scrolled_window.add(m_inner_vbox);

		m_outer_vbox.set_homogeneous(false);
		m_status_bar.push("0%");

		this->show_all_children();
	}

	void main_window::display_widgets(widget_vector t_widgets)
	{
		//clear all widgets
		auto vbox_children = this->m_inner_vbox.get_children();
		for (auto w : vbox_children)
		{
			this->m_inner_vbox.remove(*w);
		}

		//insert new
		for (const auto& w : t_widgets)
		{
			this->m_inner_vbox.pack_start(*w, Gtk::PACK_SHRINK);
		}

		this->m_inner_vbox.show_all_children();
	}

	void main_window::update_status_bar()
	{
		m_status_bar.push(std::to_string(m_scrolled_window.get_scroll_percentage()) + "%");
	}

	bool main_window::on_scroll_event(GdkEventScroll* event) // NOLINT
	{
		update_status_bar();
		return true;
	}

	bool main_window::on_key_press_event(GdkEventKey* event) // NOLINT
	{
		if (event->keyval == GDK_KEY_g)
		{
			if (this->g_pressed)
			{
				m_scrolled_window.scroll_to_top();
				update_status_bar();
			}
			else
			{
				this->g_pressed = true;
			}
			return true;
		}
		this->g_pressed = false;

		switch(event->keyval)
		{
			case GDK_KEY_q:
				this->hide();
				return true;

			case GDK_KEY_G:
				m_scrolled_window.scroll_to_bottom();
				update_status_bar();
				return true;

			case GDK_KEY_j:
				//scroll down
				m_scrolled_window.scroll_amount(this->current_config.get_value_float("vim_scroll_distance"));
				update_status_bar();
				return true;

			case GDK_KEY_k:
				//scroll up
				m_scrolled_window.scroll_amount(this->current_config.get_value_float("vim_scroll_distance") * -1);
				update_status_bar();
				return true;

			case GDK_KEY_d:
				if ((event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK) //NOLINT
				{
					//scroll down long
					m_scrolled_window.scroll_amount(this->current_config.get_value_float("vim_long_scroll_distance"));
					update_status_bar();
					return true;
				}

			case GDK_KEY_u:
				if ((event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK) //NOLINT
				{
					//scroll up long
					m_scrolled_window.scroll_amount(this->current_config.get_value_float("vim_long_scroll_distance") * -1);
					update_status_bar();
					return true;
				}
			default:
				return Gtk::Window::on_key_press_event(event);
		}
	}



	void main_window::set_file_watcher(const std::string& t_path, std::function<void()> t_callback)
	{
		//inotify
		auto file_descriptor = inotify_init1(IN_NONBLOCK);
		inotify_add_watch(file_descriptor, t_path.c_str(), IN_MODIFY);

		//timeout
		Glib::signal_timeout().connect([t_callback, this, file_descriptor](){
			if (file_is_modified(file_descriptor))
			{
				t_callback();
			}
			return true;
		}, 1000);
	}



	constexpr static const std::size_t max_path_length = 512;
	constexpr static const std::size_t event_size = sizeof(inotify_event);
	constexpr static const std::size_t buffer_length = event_size + max_path_length;

	bool main_window::file_is_modified(int t_file_descriptor)
	{
		char buffer[buffer_length];
		auto num_bytes = read(t_file_descriptor, buffer, buffer_length);
		
		return num_bytes != -1;
	}	

} //namespace minmd
