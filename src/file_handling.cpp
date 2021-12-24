#include "file_handling.h"

std::string minmd::parse_file(const std::string& file_path)
{

	//zpracovavany soubor
	std::ifstream input_file(file_path);

	//test souboru
	if (!input_file.good())
	{
		std::cerr << "Can't open file."	<< std::endl;
		exit(EXIT_FAILURE);
	}


	std::string result = "\n"; //vektor obsahujici radky

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

/*
//ulozeni souboru ze stringu
void save_file(std::string contents, std::string filename)
{
	std::ofstream file(filename);
	if (!file.good())
	{
		//hodit error
	}

	file << contents;

	file.close();
}

//ulozeni souboru z vektoru
void save_file(std::vector<std::string> contents, std::string filename)
{
	std::ofstream file(filename);
	if (!file.good())
	{
		//hodit error
	}

	for (auto s : contents)
	{
		file << s;
	}

	file.close();
}
*/
