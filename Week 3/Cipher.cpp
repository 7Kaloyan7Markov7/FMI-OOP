#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int ONE_BYTE = sizeof(int8_t);
	const int FOUR_BYTES = sizeof(int32_t);
}

size_t getSizeOfFile(std::ifstream& ifs)
{
	size_t size = 0;
	if (!ifs.is_open()) return size;

	size_t prevPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size = ifs.tellg();
	ifs.seekg(prevPos);

	return size;
}

void writeNumsInFile(std::ofstream& ofs)
{
	if (!ofs.is_open()) return;
	int size, temp = 0;

	std::cin >> size;
	for (int i = 0; i < size; ++i)
	{
		std::cin >> temp;
		ofs.write((const char*)&temp, GLOBAL_CONSTANTS::FOUR_BYTES);
	}
}

int readKey(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open()) return 0;
	int key = 0;

	ifs.read((char*)&key, GLOBAL_CONSTANTS::ONE_BYTE);
	ifs.close();

	return key;
}

void writeKey(const char* fileName)
{
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open()) return;

	int temp = 0;
	std::cin >> temp;
	if (temp < 0 || temp > 255)
	{
		std::cout << "Invalid key";
		return;
	}

	ofs.write((const char*)&temp, GLOBAL_CONSTANTS::ONE_BYTE);
	if (ofs.bad() || ofs.fail()) std::cout << "Invalid input";

	ofs.close();
}

void printSecret(std::ifstream& ifs, const char* keyFile)
{
	if (!ifs.is_open()) return;
	size_t fileSize = getSizeOfFile(ifs);
	size_t countOfNums = fileSize / GLOBAL_CONSTANTS::FOUR_BYTES;

	int key = readKey(keyFile);
	int temp = 0;

	for (int i = 0; i < countOfNums; ++i)
	{
		ifs.read((char*)&temp, GLOBAL_CONSTANTS::FOUR_BYTES);
		std::cout << temp + key;
		if (i != countOfNums - 1) std::cout << " ";
	}
}

int main()
{

	return 0;
}
