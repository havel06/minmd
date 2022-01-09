#include "image_widget.h"
#include <iostream>

namespace minmd
{
	image_widget::image_widget(const std::string& path)
	{
		auto pixbuf = Gdk::Pixbuf::create_from_file(path);

		int width = this->get_config().get_value_int("window_width");
		if (pixbuf->get_width() > width)
		{
			auto new_pixbuf = Gdk::Pixbuf::create_from_file(path, static_cast<int>(width), -1, true);
			this->set(new_pixbuf);
		}
		else
		{
			this->set(pixbuf);
		}

		this->m_path = path;	
	}

	const std::string& image_widget::get_path() const
	{
		return this->m_path;
	}


	const minmd::config*image_widget::m_config = nullptr;

	void image_widget::set_config(const minmd::config& t_config)
	{
		image_widget::m_config = &t_config;
	}


	const minmd::config& image_widget::get_config() const
	{
		return *image_widget::m_config;
	}

} //namespace minmd
