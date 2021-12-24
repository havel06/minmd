#include "parse.h"
#include "image_widget.h"
#include "main_label.h"
#include <algorithm>
#include <iostream>
#include <md4c.h>

int enter_block_callback(MD_BLOCKTYPE type, void* detail, void* userdata);
int leave_block_callback(MD_BLOCKTYPE type, void* detail, void* userdata);
int enter_span_callback(MD_SPANTYPE type, void* detail, void* userdata);
int leave_span_callback(MD_SPANTYPE type, void* detail, void* userdata);
int text_callback(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata);

std::vector<std::unique_ptr<Gtk::Widget>> minmd::parse(const std::string& src)
{
	s_userdata userdata;

	const MD_PARSER parser = 
	{
		0,
		MD_DIALECT_COMMONMARK,
		enter_block_callback,
		leave_block_callback,
		enter_span_callback,
		leave_span_callback,
		text_callback,
		nullptr,
		nullptr
	};

	md_parse(src.data(), src.size(), &parser, &userdata);

	return std::move(userdata.result);
}

int enter_block_callback(MD_BLOCKTYPE type, void* detail, void* userdata) //NOLINT
{
	auto *data = static_cast<minmd::s_userdata*>(userdata);

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
			data->is_verbatim = true;
			break;

		case MD_BLOCK_UL:
			data->is_ordered = false;
			if (data->nesting_level != 0)
			{
				std::cout << data->buffer << std::endl; // NOLINT
				data->result.push_back(std::move(std::make_unique<minmd::main_label>(std::string(data->buffer),
				                          static_cast<int>(data->nesting_level),
										  "text")));
				data->buffer.clear();
			}
			data->nesting_level++;
			break;
		case MD_BLOCK_OL:
			data->is_ordered = true;
			if (data->nesting_level != 0)
			{
				std::cout << data->buffer << std::endl; // NOLINT
				data->result.push_back(std::move(std::make_unique<minmd::main_label>(std::string(data->buffer),
				                          static_cast<int>(data->nesting_level),
										  "text")));
				data->buffer.clear();
			}
			data->nesting_level++;
			break;
		case MD_BLOCK_LI:
		{
			std::string line_begin{};
			if (data->is_ordered)
			{
				line_begin = std::to_string(data->ol_current++) + '.';
			}
			else
			{ 
				line_begin = "&#8226;";
			}
			data->buffer += line_begin + "  ";
			break;
		}
		case MD_BLOCK_QUOTE:
			data->nesting_level++;
			break;
	}

	return 0;
}
int leave_block_callback(MD_BLOCKTYPE type, void* detail, void* userdata)
{
	auto *data = static_cast<minmd::s_userdata*>(userdata);

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
			if (data->nesting_level != 0)
			{
				std::cout << data->buffer << std::endl; // NOLINT
				data->result.push_back(std::move(std::make_unique<minmd::main_label>(std::string(data->buffer), 0, "quote")));
				data->buffer.clear();
				return 0;
			}
			break;

		case MD_BLOCK_H:
		{
			std::cout << data->buffer << std::endl; // NOLINT
			std::string class_name = "heading" + std::to_string((static_cast<MD_BLOCK_H_DETAIL*>(detail))->level);
			data->result.push_back(std::move(std::make_unique<minmd::main_label>(std::string(data->buffer), 0, class_name)));
			data->buffer.clear();
			return 0;
		}

		case MD_BLOCK_CODE:
			data->is_verbatim = false;
			std::cout << data->buffer << std::endl; // NOLINT
			data->result.push_back(std::move(std::make_unique<minmd::main_label>(std::string(data->buffer), 0, "code")));
			data->buffer.clear();

		case MD_BLOCK_UL:
			data->nesting_level--;
			break;

		case MD_BLOCK_OL:
			data->nesting_level--;
			data->ol_current = 1;
			break;

		case MD_BLOCK_LI:

			break;
		case MD_BLOCK_QUOTE:
			data->nesting_level--;
			break;
	}

	if (!data->buffer.empty())
	{
		std::cout << data->buffer << std::endl; // NOLINT

		data->result.push_back(std::move(std::make_unique<minmd::main_label>(std::string(data->buffer),
		                          data->nesting_level,
								  "text")));
		data->buffer.clear();
	}

	return 0;
}

int enter_span_callback(MD_SPANTYPE type, void* detail, void* userdata)
{
	auto *data = static_cast<minmd::s_userdata*>(userdata);

	switch (type)
	{
		case MD_SPAN_U:
			break; //todo - finish me
		case MD_SPAN_A:
		{
			MD_ATTRIBUTE* href_attribute = &((static_cast<MD_SPAN_A_DETAIL*>(detail))->href);
			MD_SIZE href_size = href_attribute->substr_offsets[1]; //NOLINT
			const MD_CHAR* href_text = href_attribute->text;

			data->buffer += "<a href='" + std::string(href_text, href_size) + "'>";
			break;
		}	
		case MD_SPAN_DEL: //todo - finish me
		case MD_SPAN_LATEXMATH: //todo - maybe
		case MD_SPAN_LATEXMATH_DISPLAY: //todo - maybe
		case MD_SPAN_WIKILINK: break; // todo - maybe
		case MD_SPAN_STRONG:
			data->buffer += "<b>";
			break;
		case MD_SPAN_EM:
			data->buffer += "<i>";
			break;
		case MD_SPAN_CODE:
			data->buffer += "<tt>";
			break;
		case MD_SPAN_IMG:
		{
			MD_ATTRIBUTE* attribute = &((static_cast<MD_SPAN_IMG_DETAIL*>(detail))->src);
			MD_SIZE size = attribute->substr_offsets[1];
			const MD_CHAR* text = attribute->text;
			data->result.push_back(std::move(std::make_unique<image_widget>(std::string(text,size))));
			break;
		}
	}
	return 0;
}
int leave_span_callback(MD_SPANTYPE type, void* detail, void* userdata) //NOLINT
{
	auto *data = static_cast<minmd::s_userdata*>(userdata);

	switch (type)
	{
		case MD_SPAN_U:
			break; //todo - finish me
		case MD_SPAN_A:
			data->buffer += "</a>";
			break;
		case MD_SPAN_DEL: //todo - finish me
		case MD_SPAN_LATEXMATH: //todo - maybe
		case MD_SPAN_LATEXMATH_DISPLAY: //todo - maybe
		case MD_SPAN_WIKILINK: // todo - maybe
		case MD_SPAN_IMG:
			break;
		case MD_SPAN_STRONG:
			data->buffer += "</b>";
			break;
		case MD_SPAN_EM:
			data->buffer += "</i>";
			break;
		case MD_SPAN_CODE:
			data->buffer += "</tt>";
			break;
	}
	return 0;
}

int text_callback(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata)
{

	auto *data = static_cast<minmd::s_userdata*>(userdata);
	std::string text_s(text, size);

	if (type == MD_TEXT_BR)
	{
		data->buffer += "\n";
		return 0;
	}

	if (!data->is_verbatim)
	{
		std::replace(text_s.begin(), text_s.end(), '\n', ' ');
	}

	data->buffer += Glib::Markup::escape_text(text_s);
	return 0;
}
