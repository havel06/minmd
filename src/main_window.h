#pragma once

#include "config.h"
#include "main_grid.h"
#include "main_scrolled_window.h"
#include <gtkmm-3.0/gtkmm.h>

class main_window : public Gtk::Window
{
	public:
		explicit main_window(const minmd::config& conf);

		Gtk::Box vbox;
		main_scrolled_window scrolled_window;
		Gtk::Statusbar status_bar;
	private:
		void update_status_bar();
		bool on_key_press_event(GdkEventKey* event) override;
		bool on_scroll_event(GdkEventScroll* event) override;
		const minmd::config current_config;
		bool g_pressed = false;
};
