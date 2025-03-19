#include <iostream>
#include <cstring>
#include "FileName.h";

#pragma warning (disable : 4996);

namespace CONSTANTS
{
	const int MAX_GRADES = 6;
	const int MAX_REP_NAME = 30;
}

	void GradeReport::copyFrom(const GradeReport& other)
	{
		this->countOfGrades = other.getGradesCount();

		this->grades = new int[countOfGrades];
		for (int i = 0; i < countOfGrades; ++i)
		{
			this->grades[i] = other.grades[i];
		}

		this->reportName = new char[strlen(other.getName()) + 1];
		strcpy(this->reportName, other.getName());
	}

	void GradeReport::free()
	{
		delete[] this->grades;
		delete[] this->reportName;
		this->grades = nullptr;
		this->reportName = nullptr;
		this->countOfGrades = 0;
	}

	bool GradeReport::validateReportName(const char* reportName) const
	{
		if (!reportName) return false;
		if (strlen(reportName) > CONSTANTS::MAX_REP_NAME) return false;

		return true;
	}

	bool GradeReport::validateGrades(const int* grades, int countOfGrades) const
	{
		if (!grades) return false;
		if (countOfGrades < 0 || countOfGrades > CONSTANTS::MAX_GRADES) return false;

		return true;
	}

	GradeReport::GradeReport(const int* grades, int countOfGrades, const char* reportName)
	{
		setGrades(grades, countOfGrades);
		setReportName(reportName);
	}

	GradeReport::GradeReport(const GradeReport& other)
	{
		copyFrom(other);
	}
	
	GradeReport& GradeReport::operator=(const GradeReport& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}

		return *this;
	}

	GradeReport::~GradeReport()
	{
		free();
	}

	void GradeReport::setReportName(const char* name)
	{
		if (!validateReportName(name)) return;

		delete[] this->reportName;
		this->reportName = new char[strlen(name) + 1];

		strcpy(this->reportName, name);
	}

	void GradeReport::setGrades(const int* grades, int gradesCount)
	{
		if (!validateGrades(grades, gradesCount)) return;
		
		this->countOfGrades = gradesCount;

		delete[] this->grades;
		this->grades = new int[gradesCount];

		for (int i = 0; i < gradesCount; ++i)
		{
			this->grades[i] = grades[i];
		}
	}

	const char* GradeReport::getName() const
	{
		return this->reportName;
	}

	size_t GradeReport::getGradesCount() const
	{
		return this->countOfGrades;
	}

	double GradeReport::getAverageGrade() const
	{
		double sum = 0;
		for (int i = 0; i < countOfGrades; ++i)
		{
			sum += grades[i];
		}
		return sum / countOfGrades;
	}

	void GradeReport::print() const
	{
		std::cout << "|" << this->reportName << "|{";
		for (int i = 0; i < countOfGrades; ++i)
		{
			std::cout << this->grades[i];
			if (i != countOfGrades - 1) std::cout << ",";
		}
		std::cout << "}|" << std::endl;
	}


int main()
{
	int arr[3] = { 3,3,3 };

	GradeReport b(arr, 3, "Koki");
	b.print();

	return 0;
}
