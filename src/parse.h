/*
 * Copyright (c) 2021-2022 Michal Havlíček
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "../md4cpp/include/md4cpp.hpp"
#include "config.h"
#include "image_widget.h"

#include <gtkmm-3.0/gtkmm.h>
#include <md4c.h>
#include <memory>
#include <string>
#include <vector>

namespace minmd
{
	class parser : public md4cpp::parser
	{
	public:
		using md4cpp::parser::parser;
		[[nodiscard]] const std::vector<std::unique_ptr<Gtk::Widget>>& get_widgets() const;
	private:
		void on_enter_block(MD_BLOCKTYPE type, const md4cpp::detail_variant& detail) override;
		void on_leave_block(MD_BLOCKTYPE type, const md4cpp::detail_variant& detail) override;
		void on_enter_span(MD_SPANTYPE type, const md4cpp::detail_variant& detail) override;
		void on_leave_span(MD_SPANTYPE type, const md4cpp::detail_variant& detail) override;
		void on_text(std::string_view text, MD_TEXTTYPE type) override;

		void push_back_label(std::string_view contents, unsigned int nesting_level, std::string_view css_class);
		void push_back_image(std::string_view source);
		
		std::vector<std::unique_ptr<Gtk::Widget>> m_widgets{};
		std::string m_buffer{};

		bool m_is_verbatim = false; //whether newline chars should be displayed
		bool m_is_ordered{}; //wheter current list is an ordered list
		unsigned int m_nesting_level = 0; //current level of nesting in lists & quotes
		unsigned int m_current_ol_index = 1;
	};
} //namespace minmd
