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
#include "image_widget.h"
#include "inner_vbox.h"
#include "main_scrolled_window.h"
#include <gtkmm-3.0/gtkmm.h>

using widget_vector = const std::vector<std::unique_ptr<Gtk::Widget>>&;

namespace minmd
{
	class main_window : public Gtk::Window
	{
		public:
			explicit main_window(const minmd::config& conf);
			void display_widgets(widget_vector t_widgets);

		private:
			Gtk::Box m_outer_vbox;
			main_scrolled_window m_scrolled_window;
			Gtk::Statusbar m_status_bar;
			minmd::inner_vbox m_inner_vbox;

			const minmd::config current_config;

			void update_status_bar();
			bool on_key_press_event(GdkEventKey* event) override;
			bool on_scroll_event(GdkEventScroll* event) override;
			bool g_pressed = false;
	};
} //namespace minmd
