#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	const size_t  MAX_SIZE = 1024;
}

void selfPrint(std::ifstream& ifs)
{
	if (!ifs.is_open()) return;
	char buff[CONSTANTS::MAX_SIZE];

	while (!ifs.eof())
	{
		ifs.getline(buff, CONSTANTS::MAX_SIZE);
		std::cout << buff << std::endl;
	}

}

int main()
{
	std::ifstream ifs("FileName.cpp");
	if (!ifs.is_open()) return -1;

	selfPrint(ifs);
	ifs.close();

	return 0;
}
