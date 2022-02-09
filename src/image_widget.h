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
			static void set_config(const minmd::config& t_config);
			static const minmd::config& get_config();
		private:
			std::string m_path;
			static const minmd::config* m_config;
	};
} //namespace minmd
