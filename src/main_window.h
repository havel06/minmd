#pragma once

#include "config.h"
#include "inner_vbox.h"
#include "main_scrolled_window.h"
#include <gtkmm-3.0/gtkmm.h>

class main_window : public Gtk::Window
{
	public:
		explicit main_window(const minmd::config& conf);

		Gtk::Box m_outer_vbox;
		main_scrolled_window m_scrolled_window;
		Gtk::Statusbar m_status_bar;
		minmd::inner_vbox m_inner_vbox;
	private:
		const minmd::config current_config;
		void update_status_bar();
		bool on_key_press_event(GdkEventKey* event) override;
		bool on_scroll_event(GdkEventScroll* event) override;
		bool g_pressed = false;
};
