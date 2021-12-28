#pragma once

#include "config.h"
#include <gtkmm-3.0/gtkmm.h>

namespace minmd
{
	class image_widget : public Gtk::Image
	{
		public:
			explicit image_widget(const std::string& path);
			[[nodiscard]] const std::string& get_path() const;
			void resize_to_fit(unsigned int width);
		private:
			std::string m_path;
	};
} //namespace minmd
