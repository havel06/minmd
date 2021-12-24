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
