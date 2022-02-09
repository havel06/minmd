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

#include "config.h"
#include "main_label.h"

#include <iostream>

minmd::config::config(const std::string& config_source) // NOLINT
{
	std::string word_buffer; //drzi jakoukoliv sekvenci znaku

	std::string key_buffer; //drzi posledni nazev klice

	for (auto i : config_source)
	{
		switch (i)
		{
			//ignorovat whitespace
			case '\t':
			case '\n':
			case ' ':
				break;

			case '=':
				//ulozeni klice
				key_buffer = word_buffer;
				word_buffer.clear();
				break;

			case ';':
				//vlozeni klice a hodnoty do mapy
				try 
				{
					this->config_values.at(key_buffer) = word_buffer;
				}
				catch (std::out_of_range& err)
				{
					std::cerr << "Warning: keyword '" << key_buffer << "' is unknown, and thus ignored." << std::endl;
				}
				word_buffer.clear();
				break;

			default:
				//pricteni znaku k bufferu
				word_buffer += i;
				break;
		}
	}
}


const std::string& minmd::config::get_value_string(const std::string& key) const
{
	return this->config_values.at(key);
}
int minmd::config::get_value_int(const std::string& key) const
{
	try
	{
		return std::stoi(this->config_values.at(key)); // NOLINT
	}
	catch (std::invalid_argument& e)
	{
		throw std::runtime_error("Invalid value '" + config_values.at(key) + "' assigned to '" + key + "'");
	}
}
float minmd::config::get_value_float(const std::string& key) const
{
	try
	{
		return std::stof(this->config_values.at(key)); // NOLINT
	}
	catch (std::invalid_argument& e)
	{
		throw std::runtime_error("Invalid value '" + config_values.at(key) + "' assigned to '" + key + "'");
	}
}
