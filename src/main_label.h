#pragma once

#include "config.h"

#include <gtkmm-3.0/gtkmm.h>
#include <string>

namespace minmd
{
	class main_label : public Gtk::Label
	{
		public:
			main_label(const std::string& markup, unsigned int indent, const std::string& css_class);
			main_label(const main_label& other) = delete;

			const std::string& get_markup() const;
			const minmd::config& get_config() const;
			static void set_config(const minmd::config& t_config);

		private:
			const std::string markup_src;
			static const minmd::config* m_config;
	};
} //namespace minmd
