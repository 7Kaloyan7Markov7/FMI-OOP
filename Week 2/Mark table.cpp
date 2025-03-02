#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_NAME_SIZE = 50;
	const int FAC_NUM_SIZE = 10;
	const int MAX_STUDENTS = 50;
	const int MAX_FILENAME_SIZE = 10;
}

struct Student
{
	char name[GLOBAL_CONSTANTS::MAX_NAME_SIZE];
	char facNum[GLOBAL_CONSTANTS::FAC_NUM_SIZE];
	double averageGrade;
};


struct Table
{
	Student students[GLOBAL_CONSTANTS::MAX_STUDENTS];
	size_t currentCount;
};

void printInfo(const char* facNum)
{
	if (!facNum) return;


	
}


int main()
{
	char fileName[GLOBAL_CONSTANTS::MAX_FILENAME_SIZE];
	std::cout << "Open file:" << std::endl;
	std::cin >> fileName;



	return 0;
}
