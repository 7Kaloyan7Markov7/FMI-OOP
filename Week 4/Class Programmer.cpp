#include <iostream>

namespace CONSTANTS
{
	const int MAX_NAME_SIZE = 32;
	const int MIN_AGE = 18;
	const int MAX_AGE = 100;
	const int MAX_SALARY = 500;
	const int MIN_SALARY = 2500;
	const char DEFAULT_NAME[] = "Unknown";
	const int DEFAULT_VALUE = 0;
}

class Programmer
{
private:
	char name[CONSTANTS::MAX_NAME_SIZE];
	int age;
	int salary;
	uint8_t language; //0,1,2,4,8,16 = not_assigned, c++, python, java, c#, javascript
	
	void strCopy(const char* str)
	{
		int index = 0;
		while (str[index] != '\0')
		{
			this->name[index] = str[index];
			index++;
		}
		this->name[index] = '\0';
	}

	int strLen(const char* str) const
	{
		int index = 0;
		while (str[index] != '\0') index++;

		return index;
	}

	void bigSetter(const char* name, int age, int salary, uint8_t language)
	{
		setName(name);
		setAge(age);
		setSalary(salary);
		setLanguage(language);
	}

	bool validateName(const char* str) const
	{
		if (!str) return false;
		int len = strLen(str);

		if (len < CONSTANTS::DEFFAULT_VALUE || len > CONSTANTS::MAX_NAME_SIZE) return false;

		return true;
	}

	bool validateAge(int age) const
	{
		if (age < CONSTANTS::MIN_AGE || age > CONSTANTS::MAX_AGE) return false;

		return true;
	}

	bool validateSalary(int salary) const
	{
		if (age < CONSTANTS::MIN_SALARY || age > CONSTANTS::MAX_SALARY) return false;

		return true;
	}

	bool validateLanguage(int language) const
	{
		if (language > 16 || language <= 0) return false;

		while (!(language % 2)) language /= 2;
		return language == 1;
	}

	bool validate(const char* str, int age, int salary, int language) const
	{
		return validateName(str) && validateAge(age)
		&& validateSalary(salary) && validateLanguage(language);
	}

public:

	Programmer() : age(CONSTANTS::MIN_AGE), salary(CONSTANTS::MIN_SALARY), language(CONSTANTS::DEFAULT_VALUE)
	{
		strCopy(CONSTANTS::DEFAULT_NAME);
	}

	Programmer(const char* name, int age, int salary, int language)
	{
		if (!validate(name, age, salary, language))
		{
			std::cout << "There was an error" << std::endl;
			bigSetter(CONSTANTS::DEFAULT_NAME, CONSTANTS::MIN_AGE, CONSTANTS::MIN_SALARY, CONSTANTS::DEFAULT_VALUE);
			return;
		}
		bigSetter(name, age, salary, language);
	}

	void setName(const char* name)
	{
		strCopy(name);
	}

	void setAge(int age)
	{
		this->age = age;
	}

	void setSalary(int salary)
	{
		this->salary = salary;
	}

	void setLanguage(uint8_t language)
	{
		this->language = language;
	}
};


int main()
{
	Programmer a("koki", 20, 3000, 4);

	return 0;
}
