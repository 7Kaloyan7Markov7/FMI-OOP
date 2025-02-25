#include <iostream>
namespace CONSTANTS
{
	const int MAX_SIZE = 257;
	const int EGN_SIZE = 11;
	const int MAX_STUDENTS = 25;
}

enum Age
{
	freshman,
	sophomore,
	junior,
	senior
};

struct Student
{
	char name[CONSTANTS::MAX_SIZE] = "";
	char surrname[CONSTANTS::MAX_SIZE] = "";
	char EGN[CONSTANTS::EGN_SIZE] = "";
	Age age;
};

void fillStr(char* str, int size)
{
	if (!str) return;

	std::cin >> str;
	str[size] = '\0';
}

Student readStudent()
{
	Student res;
	int nameSize, surrNameSize, age = 0;

	std::cout << "Enter name size: ";
	std::cin >> nameSize;
	std::cout << "Enter name: ";
	fillStr(res.name, nameSize);

	std::cout << "Enter surrname size: ";
	std::cin >> surrNameSize;
	std::cout << "Enter surrname: ";
	fillStr(res.surrname, surrNameSize);

	std::cout << "Enter EGN: ";
	fillStr(res.EGN, CONSTANTS::EGN_SIZE - 1);

	std::cout << "Age: ";
	std::cin >> age;
	switch (age)
	{
		case 0: res.age = Age::freshman;
			break;
		case 1: res.age = Age::sophomore;
			break;
		case 2: res.age = Age::junior;
			break;
		case 3: res.age = Age::senior;
			break;
		default: std::cout << "Error";
			break;
	}
	
	return res;
}

void printStudent(const Student& s)
{
	std::cout << "Student name: " << s.name << std::endl;
	std::cout << "Student surrname: " << s.surrname << std::endl;
	std::cout << "Student EGN: " << s.EGN << std::endl;
	switch (s.age)
	{
	case Age::freshman: std::cout << "freshman" << std::endl;
		break;
	case Age::sophomore: std::cout << "sophomore" << std::endl;
		break;
	case Age::junior: std::cout << "junior" << std::endl;
		break;
	case Age::senior: std::cout << "senior" << std::endl;
		break;
	default: std::cout << "Error" << std::endl;
		break;
	}
 }

struct University
{
	char name[CONSTANTS::MAX_SIZE] = "";
	Student students[CONSTANTS::MAX_STUDENTS];
	int currentStudents = 0;

	bool hasStudent(const Student& s)
	{
		for (int i = 0; i < currentStudents; ++i)
		{
			if (!strcmp(s.EGN, students[i].EGN)) return true;
		}

		return false;
	}

	void addStudent(const Student& s)
	{
		if (hasStudent(s) || currentStudents >= CONSTANTS::MAX_STUDENTS) return;
		
		students[currentStudents] = s;
		currentStudents++;
	}

	void removeStudent(const char* EGN)
	{
		if (!EGN) return;
		int index = 0;

		for (int i = 0; i < currentStudents; ++i)
		{
			if (!strcmp(EGN, students[i].EGN))
			{
				index = i;
				break;
			}
		}

		if (index >= currentStudents)
		{
			std::cout << "Student is not found";
			return;
		}
		for (int i = index; i < currentStudents - 1; ++i)
		{
			students[i] = students[i + 1];
		}
		currentStudents--;
	}

	void printStudents(const Age& age)
	{
		for (int i = 0; i < currentStudents; ++i)
		{
			if (students[i].age == age)
			{
				printStudent(students[i]);
			}
		}
	}
};
