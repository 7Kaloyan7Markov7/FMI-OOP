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
	const int MAX_PROGRAMMERS = 50;
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
		setStartingLanguage(language);
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

	void setStartingLanguage(uint8_t language)
	{
		int mask = 1;
		this->language = (mask << language);
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

	uint8_t getLanguages() const
	{
		return this->language;
	}

	void printProgrammer() const
	{
		std::cout << "|" << this->name << "|";
		std::cout << this->age << "|";
		std::cout << this->salary << "|";
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

	bool programmerCmp(const Programmer& other)
	{
		if (this->salary > other.salary) return true;
		else if (this->salary == other.getSalary() && this->age > other.getAge()) return true;

		return false;
	}
};

class SoftwareCompany
{
private:
	Programmer programmers[CONSTANTS::MAX_PROGRAMMERS];
	int currentProgrammers;

	bool validateCurrentProgrammers(int currentProgrammers) const
	{
		return currentProgrammers >= 0 && currentProgrammers < CONSTANTS::MAX_PROGRAMMERS;
	}

public:
	SoftwareCompany() : currentProgrammers(CONSTANTS::DEFAULT_VALUE) {};

	void addProgrammer(const char* name, int age, int salary, uint8_t language)
	{
		if (!validateCurrentProgrammers(currentProgrammers + 1))
		{
			std::cout << "Can't add more programmers";
			return;
		}
		programmers[currentProgrammers] = Programmer(name, age, salary, language);
		this->currentProgrammers += 1;
	}

	int getCurretProgrammers() const
	{
		return this->currentProgrammers;
	}

	void printAll() const
	{
		for (int i = 0; i < this->currentProgrammers; ++i)
		{
			std::cout << "Number " << i + 1 << ": ";
			programmers[i].printProgrammer();
		}
	}

	double getAverageSalary() const
	{
		if (!this->currentProgrammers) return 0;
		double averageSalary = 0;

		for (int i = 0; i < this->currentProgrammers; ++i)
		{
			averageSalary += programmers[i].getSalary();
		}
		return averageSalary / (this->currentProgrammers);
	}

	double getAverageAge() const
	{
		if (!this->currentProgrammers) return 0;

		double averageAge = 0;
		for (int i = 0; i < this->currentProgrammers; ++i)
		{
			averageAge += this->programmers[i].getAge();
		}

		return averageAge / this->currentProgrammers;
	}

	void printByLanguage(uint8_t num)
	{
		for (int i = 0; i < currentProgrammers; ++i)
		{
			if ((programmers[i].getLanguages() >> num) & 1)
				programmers[i].printProgrammer();
		}
	}

	void teachLanguage(int number, uint8_t language)
	{
		if (number <  1 || number > CONSTANTS::MAX_PROGRAMMERS + 1)
		{
			std::cout << "Invalid number";
			return;
		}

		if (language < 0 || language > 4)
		{
			std::cout << "Invalid language";
			return;
		}

		this->programmers[number - 1].learnLanguage(language);
	}
};

int main()
{
	SoftwareCompany a;
	a.addProgrammer("koki", 20, 3001, 0);
	a.teachLanguage(1, 1);
	a.addProgrammer("yoan", 24, 3000, 1);
	a.addProgrammer("olq", 24, 3000, 0);
	a.addProgrammer("ivo", 24, 3000, 0);
	a.addProgrammer("ilian", 24, 3000, 0);
	a.printByLanguage(0);

	return 0;
}
