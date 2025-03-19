#include <iostream>
#include <cstring>
#include "Source1.h"

#pragma warning (disable : 4996)

namespace CONSTANTS
{
	const int MAX_SIZE = 30;
	const int MAX_QUOTE_SIZE = 64;
	const int MAX_GRADES_SIZE = 10;
}

void GraduatedStudent::copyFrom(const GraduatedStudent& other)
	{
		bigSetter(other.getName(), other.getQuote(), other.getGrades(), other.getCountOfGrades());
	}

void GraduatedStudent::bigSetter(const char* name, const char* quote, const int* grades, size_t countOfGrades)
	{
		setName(name);
		setQuote(quote);
		setGrades(grades, countOfGrades);
	}

void GraduatedStudent::free()
	{
		delete[] this->name;
		delete[] this->quote;
		delete[] this->grades;
		name = nullptr;
		quote = nullptr;
		grades = nullptr;
		countOfGrades = 0;
	}

bool GraduatedStudent::validateName(const char* name) const
	{
		if (!name || strlen(name) > CONSTANTS::MAX_SIZE) return false;

		return true;
	}

bool GraduatedStudent::validateQuote(const char* quote) const
	{
		if (!quote || strlen(quote) > CONSTANTS::MAX_QUOTE_SIZE) return false;

		return true;
	}

bool GraduatedStudent::validateGrades(const int* grades, size_t countOfGrades) const
	{
		if (!grades) return false;
		if (countOfGrades > CONSTANTS::MAX_GRADES_SIZE) return false;
		return true;
	}

GraduatedStudent::GraduatedStudent() : name(nullptr), quote(nullptr), grades(nullptr), countOfGrades(0) {};

GraduatedStudent::GraduatedStudent(const char* name, const char* quote, const int* grades, size_t countOfGrades)
	{
		bigSetter(name, quote, grades, countOfGrades);
	}

GraduatedStudent::GraduatedStudent(const GraduatedStudent& other)
	{
		copyFrom(other);
	}

GraduatedStudent& GraduatedStudent::operator=(const GraduatedStudent& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}

		return *this;
	}

GraduatedStudent::~GraduatedStudent()
	{
		free();
	}

void GraduatedStudent::setName(const char* name)
	{
		if (!validateName(name)) return;

		delete[] this->name;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

void GraduatedStudent::setQuote(const char* quote)
	{
		if (!validateQuote(quote)) return;

		delete[] this->quote;
		this->quote = new char[strlen(quote) + 1];
		strcpy(this->quote, quote);
	}

void GraduatedStudent::setGrades(const int* grades, size_t currentGrades)
	{
		if (!validateGrades(grades, currentGrades)) return;

		delete[] this->grades;

		this->countOfGrades = currentGrades;
		this->grades = new int[currentGrades];

		for (int i = 0; i < countOfGrades; ++i)
		{
			this->grades[i] = grades[i];
		}	
	}

const char* GraduatedStudent::getName() const
	{
		return this->name;
	}

const char* GraduatedStudent::getQuote() const
	{
		return this->quote;
	}

const int* GraduatedStudent::getGrades() const
	{
		return this->grades;
	}

size_t GraduatedStudent::getCountOfGrades() const
	{
		return this->countOfGrades;
	}

void GraduatedStudent::print() const
	{
		std::cout << "|" << name << "|";
		std::cout << quote << "|";
		std::cout << "{";
		for (int i = 0; i < countOfGrades; ++i)
		{
			std::cout << grades[i];
			if (i != countOfGrades - 1) std::cout << ",";
		}
		std::cout << "}|" << std::endl;
	}

//Example
int main()
{
	int grades[3] = { 6,6,6 };
	GraduatedStudent a("Kaloyan", "Bleach is PEAK", grades, 3);

	GraduatedStudent b = a;
	b.print();


	return 0;
}
