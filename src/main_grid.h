#pragma once

#include "config.h"
#include <gtkmm-3.0/gtkmm.h>

class main_grid : public Gtk::Grid
{
	public:
		explicit main_grid(const minmd::config &conf);
		~main_grid() = default;
};
