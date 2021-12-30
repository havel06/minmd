#pragma once

#include "config.h"
#include <gtkmm.h>

namespace minmd
{
	class inner_vbox : public Gtk::VBox
	{
	public:
		explicit inner_vbox(const minmd::config& t_config);
	};
} //namespace minmd
