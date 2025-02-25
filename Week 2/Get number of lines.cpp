#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_SIZE = 1024;
}

size_t getCountOfLines(const char* fileName)
{
	if (!fileName) return 0;

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return 0;

	size_t counter = 0;
	char buff[GLOBAL_CONSTANTS::MAX_SIZE];
	while (!ifs.eof())
	{
		ifs.getline(buff, GLOBAL_CONSTANTS::MAX_SIZE);
		counter++;
	}

	ifs.close();
	return counter;
}
