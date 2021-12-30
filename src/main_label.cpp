#include "main_label.h"
#include <iostream>

minmd::main_label::main_label(std::string_view markup, unsigned int indent, std::string_view css_class) : markup_src(markup)
{
	if (minmd::main_label::m_config == nullptr)
	{
		throw std::logic_error("The config object for main_label hasn't been set.");
	}
	this->set_markup(std::string(markup));
	this->set_selectable(minmd::main_label::m_config->get_value_int("text_selectable") != 0);
	this->set_xalign(0.0);
	this->set_yalign(0.0);
	this->set_line_wrap(true);
	this->set_hexpand(false);
	this->set_max_width_chars(0);
	this->get_style_context()->add_class({css_class.data(), css_class.size()});
	this->set_justify(Gtk::JUSTIFY_FILL);;

	if (indent != 0)
	{
		this->set_margin_start(static_cast<int>(indent) * minmd::main_label::m_config->get_value_int("indent_size"));
	}
}

const minmd::config* minmd::main_label::m_config = nullptr;

void minmd::main_label::set_config(const minmd::config& t_config)
{
	main_label::m_config = &t_config;
}

const minmd::config& minmd::main_label::get_config() const
{
	return *minmd::main_label::m_config;
}
