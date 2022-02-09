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

#include "main_scrolled_window.h"

main_scrolled_window::main_scrolled_window(const minmd::config& t_config) : m_config(t_config)
{
	this->set_halign(Gtk::ALIGN_FILL);

	this->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
}

unsigned int main_scrolled_window::get_scroll_percentage()
{
	double scroll_value = this->get_vadjustment()->get_value();
	double scroll_upper = this->get_vadjustment()->get_upper();

	auto scroll_percentage = static_cast<unsigned int>(floor(scroll_value / scroll_upper * 100)); //NOLINT

	return (scroll_percentage >= 0) ? scroll_percentage : 0;
}

void main_scrolled_window::scroll_amount(float amount)
{
	double scroll_value = this->get_vadjustment()->get_value();
	double scroll_upper = this->get_vadjustment()->get_upper();
	scroll_value += amount;
	auto new_adjustment = Gtk::Adjustment::create(scroll_value, 0, scroll_upper);
	this->set_vadjustment(new_adjustment);
}

void main_scrolled_window::scroll_to_top()
{
	double scroll_upper = this->get_vadjustment()->get_upper();
	auto new_adjustment = Gtk::Adjustment::create(0, 0, scroll_upper);
	this->set_vadjustment(new_adjustment);
}
void main_scrolled_window::scroll_to_bottom()
{
	double scroll_upper = this->get_vadjustment()->get_upper();
	auto new_adjustment = Gtk::Adjustment::create(scroll_upper, 0, scroll_upper);
	this->set_vadjustment(new_adjustment);
}
