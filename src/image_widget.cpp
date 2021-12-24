#include "image_widget.h"

image_widget::image_widget(const std::string& path) : Gtk::Image(path)
{
	this->m_path = path;	
}

const std::string& image_widget::get_path() const
{
	return this->m_path;
}
