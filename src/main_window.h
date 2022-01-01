#pragma once

#include "config.h"
#include "image_widget.h"
#include "inner_vbox.h"
#include "main_scrolled_window.h"
#include <gtkmm-3.0/gtkmm.h>

using widget_vector = const std::vector<std::unique_ptr<Gtk::Widget>>&;
using image_vector = const std::vector<minmd::image_widget*>&;

namespace minmd
{
	class main_window : public Gtk::Window
	{
		public:
			explicit main_window(const minmd::config& conf);
			void display_widgets(widget_vector t_widgets, image_vector t_images);

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
