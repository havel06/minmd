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
