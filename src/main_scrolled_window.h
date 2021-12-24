#pragma once

#include "config.h"
#include <gtkmm-3.0/gtkmm.h>

class main_scrolled_window : public Gtk::ScrolledWindow
{
	public:
		explicit main_scrolled_window(const minmd::config& t_config);
		[[nodiscard]] unsigned int get_scroll_percentage();
		void scroll_amount(float amount);
		void scroll_to_top();
		void scroll_to_bottom();
	private:
		const minmd::config& m_config;
};
