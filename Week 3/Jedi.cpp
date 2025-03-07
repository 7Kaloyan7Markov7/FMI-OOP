#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_NAME_SIZE = 50;
	const int MAX_JEDI_COUNT = 100;
	const int MAX_BUFF_SIZE = 200;
	const int NUM_OF_COLORS = 5;
	const int NUM_OF_TYPES = 3;
	const int FIRST = 0;
	const char FIRST_ROW[] = "| Jedi | age | power | lightsaber |";
	const char SEC_ROW[] = "|------|-----|-------|------------|";
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

size_t getNumOfLines(std::ifstream& ifs)
{
	size_t lines = 0;
	int prevPos = ifs.tellg();

	if (!ifs.is_open()) return lines;
	char buff[GLOBAL_CONSTANTS::MAX_BUFF_SIZE];

	while (!ifs.eof())
	{
		ifs.getline(buff,GLOBAL_CONSTANTS::MAX_BUFF_SIZE);
		lines++;
	}

	ifs.clear();
	ifs.seekg(prevPos);

	return lines;
}

void swap(Jedi& first, Jedi& sec)
{
	Jedi temp = first;
	first = sec;
	sec = temp;
}

int getHighest(const int* arr, int size)
{
	if (!arr) return -1;

	int highest = arr[GLOBAL_CONSTANTS::FIRST];
	int highestIndex = 0;

	for (size_t i = 1; i < size; ++i)
	{
		if (highest < arr[i]) highestIndex = i;
	}

	return highestIndex;
}

bool strCmp(const char* str1, const char* str2)
{
	if (!str1 && !str2) return true;
	if (!str1 || !str2) return false;
	
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

void printColor(const Color& color)
{
	switch ((int)color)
	{
	case 0: std::cout << "Red";
		break;
	case 1: std::cout << "Yellow";
		break;
	case 2: std::cout << "Green";
		break;
	case 3: std::cout << "Blue";
		break;
	case 4: std::cout << "Purple";
		break;
	case 5: std::cout << "Not assigned";
		break;
	default: std::cout << "Error";
		break;
	}
}

void printType(const Type& type)
{
	switch ((int)type)
	{
	case 0: std::cout << "Signle bladed";
		break;
	case 1: std::cout << "Double bladed";
		break;
	case 2: std::cout << "Crossguard";
		break;
	case 3: std::cout << "Not assigned";
		break;
	default: std::cout << "Error";
		break;
	}
}

Color getColor(int num)
{
	switch (num)
	{
	case 0: return Color::RED;
	case 1: return Color::YELLOW;
	case 2: return Color::GREEN;
	case 3: return Color::BLUE;
	case 4: return Color::PURPLE;
	default: return Color::NOT_ASSIGNED;
	}
}

Type getType(int num)
{
	switch (num)
	{
	case 0: return Type::SINGLE_BLADED;
	case 1: return Type::DOUBLE_BLADED;
	case 2: return Type::CROSSGUARD;
	default: return Type::NOT_ASSIGNED;
	}
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
	
	std::cout << "| " << jedi.name << " | " << jedi.age << " | " << jedi.power << " | ";
	printColor(jedi.lightSaber.color);
	std::cout << "-";
	printType(jedi.lightSaber.type);
	std::cout << " | " << std::endl;
}

void printJediCollection(const JediCollection& collection)
{
	std::cout << GLOBAL_CONSTANTS::FIRST_ROW << std::endl;
	std::cout << GLOBAL_CONSTANTS::SEC_ROW << std::endl;
	for (size_t i = 0; i < collection.currentCount; ++i)
	{
		printJedi(collection.jediArr[i]);
	}
}

void saveCollectionToBinary(const char* fileName, const JediCollection& collection)
{
	if (!fileName) return;

	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open()) return;

	ofs.write((const char*)&collection, sizeof(collection));

	ofs.close();
}

JediCollection readCollectionFromBinary(const char* fileName)
{
	JediCollection res;

	if (!fileName) return res;
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open()) return res;
	ifs.read((char*)&res, sizeof(JediCollection));

	ifs.close();
	return res;
}

void saveJediToTxt(const Jedi& jedi, std::ofstream& ofs)
{
	if (!ofs.is_open()) return;

	ofs << jedi.name << " " << jedi.age << " " << jedi.power << " " << (int)jedi.lightSaber.color << " " << (int)jedi.lightSaber.type;
}

void saveCollectionToTxt(const char* fileName, const JediCollection& collection)
{
	if (!fileName) return;

	std::ofstream ofs(fileName);
	if (!ofs.is_open()) return;
	for (size_t i = 0; i < collection.currentCount; ++i)
	{
		saveJediToTxt(collection.jediArr[i], ofs);
		if(i != collection.currentCount - 1) ofs << '\n';
	}

	ofs.close();
}

JediCollection readCollectionFromTxt(const char* fileName)
{
	JediCollection res;
	if (!fileName) return res;

	std::ifstream ifs(fileName);
	res.currentCount = getNumOfLines(ifs);
	for (size_t i = 0; i < res.currentCount; ++i)
	{
		ifs >> res.jediArr[i].name;
		ifs >> res.jediArr[i].age;
		ifs >> res.jediArr[i].power;

		int temp = 0;
		ifs >> temp;
		res.jediArr[i].lightSaber.color = getColor(temp);
		ifs >> temp;
		res.jediArr[i].lightSaber.type = getType(temp);
	}

	ifs.close();

	return res;
}

void sortByAge(JediCollection& collection)
{
	for (size_t i = 0; i < collection.currentCount - 1; ++i)
	{
		for (size_t j = 0; j < collection.currentCount - i - 1; ++j)
		{
			if (collection.jediArr[j].age > collection.jediArr[j + 1].age)
			{
				swap(collection.jediArr[j], collection.jediArr[j + 1]);
			}
		}
	}
}

void sortByPower(JediCollection& collection)
{
	for (size_t i = 0; i < collection.currentCount - 1; ++i)
	{
		for (size_t j = 0; j < collection.currentCount - i - 1; ++j)
		{
			if (collection.jediArr[j].power > collection.jediArr[j + 1].power)
			{
				swap(collection.jediArr[j], collection.jediArr[j + 1]);
			}
		}
	}
}

Color mostPopularSaberColor(const JediCollection& collection)
{
	int hist[GLOBAL_CONSTANTS::NUM_OF_COLORS] = {};
	for (size_t i = 0; i < collection.currentCount; ++i)
	{
		hist[(int)collection.jediArr[i].lightSaber.color]++;
	}
	
	int mostPop = getHighest(hist, GLOBAL_CONSTANTS::NUM_OF_COLORS);
	Color res = getColor(mostPop);
	return res;
}

Type mostPopularSaberType(const JediCollection& collection)
{
	int hist[GLOBAL_CONSTANTS::NUM_OF_TYPES] = {};
	for (size_t i = 0; i < collection.currentCount; ++i)
	{
		hist[(int)collection.jediArr[i].lightSaber.color]++;
	}

	int mostPop = getHighest(hist, GLOBAL_CONSTANTS::NUM_OF_TYPES);
	Type res = getType(mostPop);
	return res;
}

int main()
{
	
	return 0;
}
