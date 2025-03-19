#pragma once

class GradeReport
{
private:
	int* grades = nullptr;
	size_t countOfGrades = 0;
	char* reportName = nullptr;

	void copyFrom(const GradeReport& other);
	void free();

	bool validateReportName(const char* reportName) const;
	bool validateGrades(const int* grades, int countOfGrades) const;
public:

	GradeReport() = default;
	GradeReport(const int* grades, int countOfGrades, const char* reportName);
	GradeReport(const GradeReport& other);
	GradeReport& operator=(const GradeReport& other);
	~GradeReport();

	void setReportName(const char* name);
	void setGrades(const int* grades, int gradesCount);

	const char* getName() const;
	size_t getGradesCount() const;
	double getAverageGrade() const;
	
	void print() const;
};
