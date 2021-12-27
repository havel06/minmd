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
