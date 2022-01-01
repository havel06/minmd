#pragma once

#include "config.h"
#include <string>
#include <gtkmm.h>

namespace minmd
{
	void init_css(const std::string& t_css_path);
	[[nodiscard]] std::string get_config_dir();
	[[nodiscard]] minmd::config init_config(const std::string& t_path);
	[[nodiscard]] std::string get_input(int argc, char* argv[]);
}
