#include "main_grid.h"
#include <string>

main_grid::main_grid(const minmd::config &conf)
{
	this->set_row_spacing(conf.get_value_int("row_spacing"));
	this->set_halign(Gtk::ALIGN_CENTER);
}
