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
