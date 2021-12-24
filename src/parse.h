#pragma once

#include "config.h"
#include <gtkmm-3.0/gtkmm.h>
#include <memory>
#include <md4c.h>
#include <string>
#include <vector>

namespace minmd
{
	struct s_userdata
	{
		std::vector<std::unique_ptr<Gtk::Widget>> result{};
		std::string buffer{};
		bool is_ordered = false; //whether current list is an ordered list
		unsigned int ol_current = 1; //current index of ordered list
		unsigned int nesting_level = 0; //current level of nesting in lists & quotes
		bool is_verbatim = false; //whether text should be displayed with newline chars
	};

	std::vector<std::unique_ptr<Gtk::Widget>> parse(const std::string& src);
} //namespace minmd
