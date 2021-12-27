#pragma once

#include <gtkmm-3.0/gtkmm.h>

class image_widget : public Gtk::Image
{
	public:
		explicit image_widget(const std::string& path);
		[[nodiscard]] const std::string& get_path() const;
	private:
		std::string m_path;
};
