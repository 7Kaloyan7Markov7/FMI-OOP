#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_NAME_SIZE = 50;
	const int MAX_GRADES_SIZE = 100;
}

enum Major
{
	SE,
	CS,
	IS,
	I,
};

struct FMIStudent
{
	char name[GLOBAL_CONSTANTS::MAX_NAME_SIZE];
	size_t years;
	int grades[GLOBAL_CONSTANTS::MAX_GRADES_SIZE];
	int countOfSubjects = 3;
	Major major;
};

void saveStudentToFile(const FMIStudent& s, std::ofstream& ofs)
{
	if (!ofs.is_open()) return;
	ofs << s.name << '\n';

	ofs << s.years << '\n';

	for (int i = 0; i < s.countOfSubjects; ++i)
	{
		ofs << s.grades[i];
		if (i != s.countOfSubjects - 1) ofs << " ";
	}

	ofs << '\n';
	ofs << s.major << '\n';
}

void readStudentFromFile(FMIStudent& s, std::ifstream& ifs)
{
	if (!ifs.is_open()) return;
	ifs.getline(s.name,GLOBAL_CONSTANTS::MAX_NAME_SIZE);
	ifs >> s.years;
	for (int i = 0; i < s.countOfSubjects; ++i)
	{
		ifs >> s.grades[i];
	}

	int num = 0;
	ifs >> num;

	switch (num)
	{
	case 0: s.major = Major::SE;
		break;
	case 1: s.major = Major::CS;
		break;
	case 2: s.major = Major::IS;
		break;
	case 3: s.major = Major::I;
		break;
	default: std::cout << "Error";
		break;
	}

}

void writeStudentArrayToFile(const char* fileName, const FMIStudent* students, size_t size)
{
	if (!fileName) return;
	std::ofstream ofs("test.txt");
	if (!ofs.is_open()) return;

	for (size_t i = 0; i < size; ++i)
	{
		saveStudentToFile(students[i], ofs);
	}
	ofs.close();
}

FMIStudent* readStudentArrayFromFile(const char* fileName, size_t& size)
{
	FMIStudent* res = new FMIStudent[size];
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return nullptr;

	for (size_t i = 0; i < size; ++i)
	{
		readStudentFromFile(res[i], ifs);
	}

	ifs.close();
}

void printStudent(const FMIStudent& res)
{
	std::cout << res.name << " ";
	std::cout << res.years << " ";
	std::cout << "{ ";
	for (int i = 0; i < res.countOfSubjects; ++i)
	{
		std::cout << res.grades[i];
		if (i != res.countOfSubjects - 1) std::cout << ",";
	}
	std::cout << " } ";

	switch (res.major)
	{
	case 0: std::cout << "SE";
		break;
	case 1: std::cout << "CS";
		break;
	case 2: std::cout << "IS";
		break;
	case 3: std::cout << "I";
		break;
	default: std::cout << "Error";
		break;
	}
	std::cout << std::endl;
}

int main()
{

	FMIStudent s{ "Name",19,{3,3,3},3,Major::SE };	
	FMIStudent s2{ "Name2",20,{3,3,4},3,Major::CS };
	FMIStudent arr[2] = { s, s2 };
	
	writeStudentArrayToFile("test.txt", arr, 2);
	size_t size = 2;

	FMIStudent* res = readStudentArrayFromFile("test.txt", size);
	
	for (int i = 0; i < 2; ++i)
	{
		printStudent(res[i]);
	}

	return 0;
}
