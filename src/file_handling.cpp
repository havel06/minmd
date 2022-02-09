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

#include "file_handling.h"

std::string minmd::parse_file(const std::string& file_path)
{
	//zpracovavany soubor
	std::ifstream input_file(file_path);

	//test souboru
	if (!input_file.good())
	{
		throw std::runtime_error("Error occured when trying to read from file '" + file_path + "'.");
		exit(EXIT_FAILURE);
	}

	std::string result{}; //vektor obsahujici radky
	std::string line; //aktualni radek

	//cykleni skrze radky
	while (std::getline(input_file, line))
	{
		result += line;
		result += '\n';
	}

	//zavreni souboru	
	input_file.close();

	return result;
}
