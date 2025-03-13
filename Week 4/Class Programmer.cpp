#include <iostream>

namespace CONSTANTS
{
	const int MAX_NAME_SIZE = 32;
	const int MIN_AGE = 18;
	const int MAX_AGE = 100;
	const int MAX_SALARY = 5000;
	const int MIN_SALARY = 2500;
	const char DEFAULT_NAME[] = "Unknown";
	const int DEFAULT_VALUE = 0;
	const int NUM_OF_LANGUAGES = 5;
}

class Programmer
{
private:
	char name[CONSTANTS::MAX_NAME_SIZE];
	int age;
	int salary;
	uint8_t language; //0,1,2,3,4 = c++, python, java, c#, javascript

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

		if (len < CONSTANTS::DEFAULT_VALUE || len > CONSTANTS::MAX_NAME_SIZE) return false;

		return true;
	}

	bool validateAge(int age) const
	{
		if (age < CONSTANTS::MIN_AGE || age > CONSTANTS::MAX_AGE) return false;

		return true;
	}

	bool validateSalary(int salary) const
	{
		if (salary < CONSTANTS::MIN_SALARY || salary > CONSTANTS::MAX_SALARY) return false;

		return true;
	}

	bool validateLanguage(int language) const
	{
		if (language > 4 || language < 0) return false;

		return true;
	}

	bool validate(const char* str, int age, int salary, int language) const
	{
		return validateName(str) && validateAge(age)
			&& validateSalary(salary) && validateLanguage(language);
	}

	void printName() const
	{
		std::cout << this->name;
	}

	void printAge() const
	{
		std::cout << this->age;
	}

	void printSalary() const
	{
		std::cout << this->salary;
	}

	void printLanguages() const
	{
		if (!this->language) std::cout << "not asigned";
		int mask = 1;
		for (int i = 0; i < CONSTANTS::NUM_OF_LANGUAGES; ++i)
		{
			if ((language >> i) & mask)
			{
				switch (i)
				{
				case 0: std::cout << "C++ ";
					break;
				case 1: std::cout << "Python ";
					break;
				case 2: std::cout << "java ";
					break;
				case 3: std::cout << "C# ";
					break;
				case 4: std::cout << "JavaSript ";
					break;
				default: break;
				}
			}
		}
	}

	void setAge(int age)
	{
		this->age = age;
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

	void setSalary(int salary)
	{
		if (!validateSalary(salary))
		{
			this->salary = CONSTANTS::DEFAULT_VALUE;
			return;
		};
		this->salary = salary;
	}

	void setLanguage(uint8_t language)
	{
		int mask = 1;
		this-> language =  (mask << language);
	}

	const char* getName() const
	{
		return this->name;
	}

	int getAge() const
	{
		return this->age;
	}

	int getSalary() const
	{
		return this->salary;
	}

	uint8_t getLangueges() const
	{
		return this->language;
	}

	void printProgrammer() const
	{
		std::cout << "|";
		printName();
		std::cout << "|";
		printAge();
		std::cout << "|";
		printSalary();
		std::cout << "|";
		printLanguages();
		std::cout << "\b" << "|" << std::endl;
	}

	void learnLanguage(uint8_t num)
	{
		if (num < 0 || num > 4)
		{
			std::cout << "invalid language";
			return;
		}
		int mask = 1;
		this-> language =  (mask << num) | this-> language;
	}
};

int main()
{
	Programmer a("Pepi", 20, 3000, 0);
	a.printProgrammer();
	a.learnLanguage(1);
	a.learnLanguage(2);
	a.learnLanguage(3);
	a.learnLanguage(4);
	a.printProgrammer();

	return 0;
}
