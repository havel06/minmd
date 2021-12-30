#pragma once

#include "../md4cpp/include/md4cpp.hpp"
#include "config.h"
#include "image_widget.h"

#include <gtkmm-3.0/gtkmm.h>
#include <memory>
#include <md4c.h>
#include <string>
#include <vector>

namespace minmd
{
	class parser : public md4cpp::parser
	{
	public:
		using md4cpp::parser::parser;
		[[nodiscard]] const std::vector<std::unique_ptr<Gtk::Widget>>& get_widgets() const;
		[[nodiscard]] const std::vector<minmd::image_widget*>& get_images() const;
	private:
		void on_enter_block(MD_BLOCKTYPE type, md4cpp::detail_variant detail) override;
		void on_leave_block(MD_BLOCKTYPE type, md4cpp::detail_variant detail) override;
		void on_enter_span(MD_SPANTYPE type, md4cpp::detail_variant detail) override;
		void on_leave_span(MD_SPANTYPE type, md4cpp::detail_variant detail) override;
		void on_text(std::string_view text, MD_TEXTTYPE type) override;

		void push_back_label(std::string_view contents, unsigned int nesting_level, std::string_view css_class);
		void push_back_image(std::string_view source);
		
		std::vector<std::unique_ptr<Gtk::Widget>> m_widgets{};
		std::vector<minmd::image_widget*> m_images{};
		std::string m_buffer{};

		bool m_is_verbatim = false; //whether newline chars should be displayed
		bool m_is_ordered{}; //wheter current list is an ordered list
		unsigned int m_nesting_level = 0; //current level of nesting in lists & quotes
		unsigned int m_current_ol_index = 1;
	};
} //namespace minmd
