#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_NAME_SIZE = 50;
	const int MAX_JEDI_COUNT = 100;
}

enum class Color
{
	RED,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE,
	NOT_ASSIGNED,
};

enum class Type
{
	SINGLE_BLADED,
	DOUBLE_BLADED,
	CROSSGUARD,
	NOT_ASSIGNED,
};

struct LightSaber
{
	Color color = Color::NOT_ASSIGNED;
	Type type = Type::NOT_ASSIGNED;
};

struct Jedi
{
	char name[GLOBAL_CONSTANTS::MAX_NAME_SIZE] = "";
	size_t age = 0;
	size_t power = 0;
	LightSaber lightSaber;
};

struct JediCollection
{
	Jedi jediArr[GLOBAL_CONSTANTS::MAX_JEDI_COUNT];
	size_t currentCount = 0;
};

size_t sizeOfFile(const char* fileName)
{
	size_t size = 0;
	if (!fileName) return size;
	
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return size;

	size_t prevPos = ifs.tellg();
	ifs.seekg(std::ios::end);
	size = ifs.tellg();
	ifs.seekg(prevPos);

	ifs.close();

	return size;
}

size_t strLen(const char* str)
{
	size_t index = 0;
	if (!str) return index;

	while (str[index] != '\0') index++;
	return index;
}

bool strCmp(const char* str1, const char* str2)
{
	size_t size1 = strLen(str1);
	size_t size2 = strLen(str2);
	if (size1 != size2) return false;

	size_t index = 0;
	while (str1[index] == str2[index] && str1[index] != '\0') index++;

	return index == size1;
}

void strCopy(const char* source, char* dest)
{
	if (!source || !dest) return;

	size_t index = 0;
	while (source[index] != '\0')
	{
		dest[index] = source[index];
		index++;
	}
	dest[index] = '\0';
}

Jedi createJedi(const char* name, size_t age, size_t power, const LightSaber& saber)
{
	Jedi res;

	if (!name) return res;
	strCopy(name, res.name);
	res.age = age;
	res.power = power;
	res.lightSaber = saber;
	
	return res;
}

Jedi createJedi(const char* name, size_t age, size_t power, const Color& color, const Type& type)
{
	Jedi res;

	if (!name) return res;
	strCopy(name, res.name);
	res.age = age;
	res.power = power;
	res.lightSaber.color = color;
	res.lightSaber.type = type;

	return res;
}

void addJedi(JediCollection& collection, const Jedi& jedi)
{
	collection.jediArr[collection.currentCount] = jedi;
	collection.currentCount++;
}

void removeJedi(JediCollection& collection, const char* name)
{
	if (!name) return;
	int index = -1;

	for (size_t i = 0; i < collection.currentCount; ++i)
	{
		if (strCmp(name, collection.jediArr[i].name))
		{
			index = i;
			break;
		}
	}

	if (index == -1) return;

	for (size_t i = index; i < collection.currentCount - 1; ++i)
	{
		collection.jediArr[i] = collection.jediArr[i + 1];
	}
	collection.currentCount--;
}

void printJedi(const Jedi& jedi)
{
	std::cout << "Jedi: " << std::endl;
	std::cout << "Name: " << jedi.name << std::endl;
	std::cout << "Age: " << jedi.age << std::endl;
	std::cout << "Power: " << jedi.power << std::endl;
	std::cout << "Saber: " << (int)jedi.lightSaber.color << "," << (int)jedi.lightSaber.type << std::endl;
}

void printJediCollection(const JediCollection& collection)
{
	for (size_t i = 0; i < collection.currentCount; ++i)
	{
		printJedi(collection.jediArr[i]);
	}
}

void saveJediToBinary(const Jedi& jedi, std::ofstream& ofs)
{
	ofs.write((const char*)&jedi, sizeof(jedi));
}

void saveCollectionToBinary(const char* fileName, const JediCollection& collection)
{
	if (!fileName) return;

	std::ofstream ofs(fileName,std::ios::binary);
	if (!ofs.is_open()) return;

	for (size_t i = 0; i < collection.currentCount; ++i)
	{
		saveJediToBinary(collection.jediArr[i], ofs);
	}

	ofs.close();
}

JediCollection readCollectionFromBinary(const char* fileName)
{
	JediCollection res;
	
	if (!fileName) return res;
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open()) return res;
	size_t size = sizeOfFile(fileName);
	size_t sizeOfJedi = sizeof(Jedi);

	for (size_t i = 0; i < size / sizeOfJedi; ++i)
	{
		ifs.read((char*)&res.jediArr[i], sizeof(Jedi));
	}



	ifs.close();
	return res;
}

int main()
{

	return 0;
}
