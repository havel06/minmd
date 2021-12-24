#include "main_window.h"
#include <cmath>
#include <iostream>

main_window::main_window(const minmd::config& conf) : current_config(conf), scrolled_window(conf), vbox(Gtk::ORIENTATION_VERTICAL)
{
	this->set_title("testing window");
	this->set_size_request(this->current_config.get_value_int("window_width"),
	                       this->current_config.get_value_int("window_height"));
	this->set_border_width(0);

	this->add(vbox);
	vbox.pack_start(scrolled_window);
	vbox.pack_end(status_bar, false, false);
	vbox.set_homogeneous(false);
	status_bar.push("0%");
}

void main_window::update_status_bar()
{
	status_bar.push(std::to_string(scrolled_window.get_scroll_percentage()) + "%");
}

bool main_window::on_scroll_event(GdkEventScroll* event) // NOLINT
{
	update_status_bar();
	return true;
}

bool main_window::on_key_press_event(GdkEventKey* event) // NOLINT
{
	if (event->keyval == GDK_KEY_g)
	{
		if (this->g_pressed)
		{
			scrolled_window.scroll_to_top();
			update_status_bar();
		}
		else
		{
			this->g_pressed = true;
		}
		return true;
	}
	this->g_pressed = false;

	switch(event->keyval)
	{
		case GDK_KEY_q:
			this->hide();
			return true;

		case GDK_KEY_G:
			scrolled_window.scroll_to_bottom();
			update_status_bar();
			return true;

		case GDK_KEY_j:
			//scroll down
			scrolled_window.scroll_amount(this->current_config.get_value_float("vim_scroll_distance"));
			update_status_bar();
			return true;

		case GDK_KEY_k:
			//scroll up
			scrolled_window.scroll_amount(this->current_config.get_value_float("vim_scroll_distance") * -1);
			update_status_bar();
			return true;

		case GDK_KEY_d:
			if ((event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK) //NOLINT
			{
				//scroll down long
				scrolled_window.scroll_amount(this->current_config.get_value_float("vim_long_scroll_distance"));
				update_status_bar();
				return true;
			}

		case GDK_KEY_u:
			if ((event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK) //NOLINT
			{
				//scroll up long
				scrolled_window.scroll_amount(this->current_config.get_value_float("vim_long_scroll_distance") * -1);
				update_status_bar();
				return true;
			}
		default:
			return Gtk::Window::on_key_press_event(event);
	}
}
