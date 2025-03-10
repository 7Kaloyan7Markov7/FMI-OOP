#include <iostream>
#include <cstring>
#include <fstream>

namespace GLOBAL_CONSTANTS
{

	const size_t MIN_YEAR = 1918;
	const size_t MAX_YEAR = 2025;
	const size_t MIN_SPEED = 0;
	const size_t MAX_SPEED = 200;

}

namespace GLOBAL_FUNCTIONS
{

	bool isInRange(int num, const int lowerBound, const int upperBound)
	{

		return  num >= lowerBound && num <= upperBound;

	};

	bool isNullPtr(const int* arr) { return !arr; };

	bool isNullPtr(const char* str) { return !str; };

}

class Car
{
private:

	char* brandName = nullptr;
	size_t yearOfRelease = 0;
	size_t maxSpeed = 0;
	int* kilometersPassed = nullptr;

	void free()
	{
		delete[] brandName;
		brandName = nullptr;
		delete[] kilometersPassed;
		kilometersPassed = nullptr;
	}

public:

	Car(const char* name, int year, int maxSpeed, int size,const int* kilometers)
	{
		setBrandName(name);
		setReleaseYear(year);
		setMaxSpeed(maxSpeed);
		setKilometers(size, kilometers);
	}

	void setBrandName(const char* name)
	{

		if (GLOBAL_FUNCTIONS::isNullPtr(name)) return;
		if (!GLOBAL_FUNCTIONS::isNullPtr(this->brandName))
		{

			size_t len = strlen(name);
			char* newData = new char[len + 1];
			strncpy(newData, name, len);
			newData[len] = '\0';

			delete[] brandName;
			brandName = newData;

		}
		else
		{

			this->brandName = new char[strlen(name) + 1];
			strcpy(this->brandName, name);

		}

	}

	void setReleaseYear(int num)
	{
		if (!GLOBAL_FUNCTIONS::isInRange(num, GLOBAL_CONSTANTS::MIN_YEAR, GLOBAL_CONSTANTS::MAX_YEAR))
			return;

		this->yearOfRelease = num;
	}

	void setMaxSpeed(int num)
	{
		if (!GLOBAL_FUNCTIONS::isInRange(num, GLOBAL_CONSTANTS::MIN_SPEED, GLOBAL_CONSTANTS::MAX_SPEED))
			return;
		this->maxSpeed = num;
	}

	void setKilometers(int size, const int* kilometers)
	{
		if (GLOBAL_FUNCTIONS::isNullPtr(kilometers)) return;
		
		this->kilometersPassed = new int[size];
		for (int i = 0; i < size; ++i)
		{
			this->kilometersPassed[i] = kilometers[i];
		}
	}

	const char* getBrandName() const
	{
		return this->brandName;
	}

	const size_t getYear() const
	{
		return this->yearOfRelease;
	}

	const size_t getSpeed() const
	{
		return this->maxSpeed;
	}

	const int* getKilometers() const
	{
		return this->kilometersPassed;
	}

	void saveToFile(std::ofstream& ofs) const
	{
		if (!ofs.is_open()) return;

		
	}

	~Car()
	{
		free();
	}

};

int main()
{

	return 0;

}
