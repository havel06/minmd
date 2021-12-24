#pragma once

#include <string>
#include <unordered_map>

namespace minmd
{
	class config
	{
	public:
		config() noexcept = default;
		explicit config(const std::string& config_source);
		explicit config(const minmd::config& other) = default;
		config& operator=(const config& other) = default;
		explicit config(minmd::config&& other) = default;
		config& operator=(minmd::config&& other) = default;

		[[nodiscard]] const std::string& get_value_string(const std::string& key) const;
		[[nodiscard]] int get_value_int(const std::string& key) const;
		[[nodiscard]] float get_value_float(const std::string& key) const;
	private:
		std::unordered_map<std::string, std::string> config_values = {
			{"row_spacing", "20"},
			{"max_line_width", "-1"},
			{"window_width", "800"},
			{"window_height", "600"},
			{"indent_size", "20"},
			{"vim_scroll_distance", "30"},
			{"vim_long_scroll_distance", "300"},
			{"text_selectable", "0"}
		};
	};
} //namespace minmd
