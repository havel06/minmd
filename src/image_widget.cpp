#include "image_widget.h"
#include <iostream>

namespace minmd
{
	image_widget::image_widget(const std::string& path) : Gtk::Image(path)
	{
		this->m_path = path;	
	}

	const std::string& image_widget::get_path() const
	{
		return this->m_path;
	}

	void image_widget::resize_to_fit(unsigned int t_width)
	{
		if (this->get_allocated_width() > t_width)
		{
			auto new_pixbuf = Gdk::Pixbuf::create_from_file(this->get_path(), t_width, -1, true);
			this->set(new_pixbuf);
		}
	}
} //namespace minmd
