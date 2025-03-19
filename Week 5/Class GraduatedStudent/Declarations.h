#pragma once

class GraduatedStudent
{
private:
	char* name = nullptr;
	char* quote = nullptr;
	int* grades = nullptr;
	size_t countOfGrades = 0;

	void copyFrom(const GraduatedStudent& other);
	void bigSetter(const char* name, const char* quote, const int* grades, size_t countOfGrades);
	void free();

	bool validateName(const char* name) const;
	bool validateQuote(const char* quote) const;
	bool validateGrades(const int* grades, size_t countOfGrades) const;

public:
	GraduatedStudent();
	GraduatedStudent(const char* name, const char* quote, const int* grades, size_t countOfGrades);
	GraduatedStudent(const GraduatedStudent& other);
	GraduatedStudent& operator=(const GraduatedStudent& other);
	~GraduatedStudent();

	void setName(const char* name);
	void setQuote(const char* quote);
	void setGrades(const int* grades, size_t currentGrades);

	const char* getName() const;
	const char* getQuote() const;
	const int* getGrades() const;
	size_t getCountOfGrades() const;

	void print() const;
};
