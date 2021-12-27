#include "parse.h"
#include "image_widget.h"
#include "main_label.h"
#include <algorithm>
#include <iostream>
#include <md4c.h>

namespace minmd
{
	const std::vector<std::unique_ptr<Gtk::Widget>>& parser::get_widgets() const
	{
		return this->m_widgets;
	}

	void parser::on_enter_block(MD_BLOCKTYPE type, md4cpp::detail_variant detail)
	{
		switch (type)
		{
			case MD_BLOCK_DOC:
			case MD_BLOCK_HTML:
			case MD_BLOCK_HR: //todo
			case MD_BLOCK_TABLE:  //todo - maybe
			case MD_BLOCK_THEAD:  //todo - maybe
			case MD_BLOCK_TBODY:  //todo - maybe
			case MD_BLOCK_TR:  //todo - maybe
			case MD_BLOCK_TH:  //todo - maybe
			case MD_BLOCK_TD:  //todo - maybe
			case MD_BLOCK_P: 
			case MD_BLOCK_H:

			case MD_BLOCK_CODE:
				this->m_is_verbatim = true;
				break;

			case MD_BLOCK_UL:
				this->m_is_ordered = false;
				if (this->m_nesting_level != 0)
				{
					this->push_back_label(this->m_buffer, this->m_nesting_level, "text");
					this->m_buffer.clear();
				}
				this->m_nesting_level++;
				break;

			case MD_BLOCK_OL:
				this->m_is_ordered = true;
				this->m_current_ol_index = std::get<md4cpp::block_ol_detail>(detail).start;
				if (this->m_nesting_level != 0)
				{
					this->push_back_label(this->m_buffer, this->m_nesting_level, "text");
					this->m_buffer.clear();
				}
				this->m_nesting_level++;
				break;
			case MD_BLOCK_LI:
			{
				std::string line_begin{};
				if (this->m_is_ordered)
				{
					line_begin = std::to_string(this->m_current_ol_index++) + '.';
				}
				else
				{ 
					line_begin = "&#8226;";
				}
				this->m_buffer += line_begin + "  ";
				break;
			}
			case MD_BLOCK_QUOTE:
				this->m_nesting_level++;
				break;
		}
	}
	void parser::on_leave_block(MD_BLOCKTYPE type, md4cpp::detail_variant detail)
	{
		switch (type)
		{
			case MD_BLOCK_DOC:
			case MD_BLOCK_HTML: 
			case MD_BLOCK_HR: //todo
			case MD_BLOCK_TABLE: //todo - maybe
			case MD_BLOCK_THEAD: //todo - maybe
			case MD_BLOCK_TBODY: //todo - maybe
			case MD_BLOCK_TR: //todo - maybe
			case MD_BLOCK_TH: //todo - maybe
			case MD_BLOCK_TD: //todo - maybe

			case MD_BLOCK_P:
				if (this->m_nesting_level != 0)
				{
					this->push_back_label(this->m_buffer, 0, "quote");
					this->m_buffer.clear();
					return;
				}
				break;

			case MD_BLOCK_H:
			{
				unsigned int level = std::get<md4cpp::block_h_detail>(detail).level;
				this->push_back_label(this->m_buffer, 0, "heading" + std::to_string(level));
				this->m_buffer.clear();
				return;
			}

			case MD_BLOCK_CODE:
				this->m_is_verbatim = false;
				this->push_back_label(this->m_buffer, 0, "code");
				this->m_buffer.clear();
				return;

			case MD_BLOCK_UL:
			case MD_BLOCK_OL:
			case MD_BLOCK_QUOTE:
				if (this->m_nesting_level != 0)
				{
					this->m_nesting_level--;
				}
				break;

			case MD_BLOCK_LI:
				break;
		}

		if (!this->m_buffer.empty())
		{
			this->push_back_label(this->m_buffer, this->m_nesting_level, "text");
			this->m_buffer.clear();
		}
	}

	void parser::on_enter_span(MD_SPANTYPE type, md4cpp::detail_variant detail)
	{
		switch (type)
		{
			case MD_SPAN_U:
				break; //todo - finish me
			case MD_SPAN_A:
			{
				auto a_detail = std::get<md4cpp::span_a_detail>(detail);
				this->m_buffer += "<a href='";
				for (auto& s : a_detail.href.get_substrings())
				{
					if (s.type == MD_TEXT_NORMAL)
					{
						this->m_buffer += s.text;	
					}
				}
				this->m_buffer += "'>";
				break;
			}	
			case MD_SPAN_DEL:
				this->m_buffer += "<s>";
				break;
			case MD_SPAN_LATEXMATH: //todo - maybe
			case MD_SPAN_LATEXMATH_DISPLAY: //todo - maybe
			case MD_SPAN_WIKILINK: break; // todo - maybe
			case MD_SPAN_STRONG:
				this->m_buffer += "<b>";
				break;
			case MD_SPAN_EM:
				this->m_buffer += "<i>";
				break;
			case MD_SPAN_CODE:
				this->m_buffer += "<tt>";
				break;
			case MD_SPAN_IMG:
			{
				auto img_detail = std::get<md4cpp::span_img_detail>(detail);
				std::string src{};
				for (auto& s : img_detail.src.get_substrings())
				{
					if (s.type == MD_TEXT_NORMAL)
					{
						src += s.text;
					}
				}
				this->push_back_image(src);
				break;
			}
		}
	}

	void parser::on_leave_span(MD_SPANTYPE type, md4cpp::detail_variant detail)
	{
		switch (type)
		{
			case MD_SPAN_U:
				break; //todo - finish me
			case MD_SPAN_A:
				this->m_buffer += "</a>";
				break;
			case MD_SPAN_DEL:
				this->m_buffer += "</s>";
				break;
			case MD_SPAN_LATEXMATH: //todo - maybe
			case MD_SPAN_LATEXMATH_DISPLAY: //todo - maybe
			case MD_SPAN_WIKILINK: // todo - maybe
			case MD_SPAN_IMG:
				break;
			case MD_SPAN_STRONG:
				this->m_buffer += "</b>";
				break;
			case MD_SPAN_EM:
				this->m_buffer += "</i>";
				break;
			case MD_SPAN_CODE:
				this->m_buffer += "</tt>";
				break;
		}
	}
	void parser::on_text(std::string_view text, MD_TEXTTYPE type)
	{
		if (type == MD_TEXT_BR)
		{
			this->m_buffer += "\n";
			return;
		}
		if (!this->m_is_verbatim)
		{
			std::string text_edited(text);
			std::replace(text_edited.begin(), text_edited.end(), '\n', ' ');
			this->m_buffer += Glib::Markup::escape_text(text_edited);
		}
		else
		{
			this->m_buffer += Glib::Markup::escape_text({text.data(), text.size()});
		}
	}

	void parser::push_back_label(std::string_view contents, unsigned int nesting_level, std::string_view css_class)
	{
		auto widget = std::make_unique<minmd::main_label>(contents, nesting_level, css_class);
		this->m_widgets.push_back(std::move(widget));
	}

	void parser::push_back_image(std::string_view source)
	{
		auto widget = std::make_unique<image_widget>(std::string(source));
		this->m_widgets.push_back(std::move(widget));
	}
} //namespace minmd
