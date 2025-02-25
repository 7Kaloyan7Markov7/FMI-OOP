#include <iostream>
#include <fstream>

size_t getNumOfOc(const char* fileName, char ch)
{
	if (!fileName) return 0;

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return 0;

	size_t counter = 0;

	while (!ifs.eof())
	{
		if (ifs.get() == ch) counter++;
	}

	ifs.close();
	return counter;
}
