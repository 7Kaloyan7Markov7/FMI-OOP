#include <iostream>
#include <fstream>

size_t getFileSize(const char* fileName)
{
	if (!fileName) return 0;

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return 0;

	size_t prevPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t fileSize = ifs.tellg();
	ifs.seekg(prevPos);

	ifs.close();

	return fileSize;
}

int main()
{
	std::cout << getFileSize("FileName.cpp");

	return 0;
}
