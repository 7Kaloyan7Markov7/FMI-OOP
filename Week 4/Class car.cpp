#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_SPEED = 200;
	const int MIN_SPEED = 50;
	const int MAX_YEAR = 2025;
	const int MIN_YEAR = 1920;
}

class Car
{
private:
	char* brandName = nullptr;
	size_t year = 0;
	size_t maxSpeed = 0;
	int* kilometers = nullptr;
	int currentSize = 0;

	void free()
	{
		delete[] brandName;
		brandName = nullptr;
		delete[] kilometers;
		kilometers = nullptr;
	}

	size_t strLen(const char* str) const
	{
		size_t index = 0;
		while (str[index] != '\0') index++;

		return index;
	} 

	void strCopy(const char* source, char* dest)
	{
		if (!source) return;

		size_t index = 0;
		while (source[index] != '\0')
		{
			dest[index] = source[index];
			index++;
		}
		dest[index] = '\0';
	}

	bool strCmp(const char* first, const char* sec) const
	{
		if (!first || !sec) return false;

		size_t sizeFirst = strLen(first);
		size_t sizeSec = strLen(sec);
		if (sizeFirst != sizeSec) return false;
		
		int index = 0;
		while (first[index] == sec[index] && first[index] != '\0') index++;

		if (index != sizeFirst) return false;

		return true;
	}

public:

	Car(const char* name, int year, int maxSpeed, int* kilometers, int size)
	{
		setName(name);
		setYear(year);
		setMaxSpeed(maxSpeed);
		setKilometers(kilometers, size);
	}

	void setName(const char* name)
	{
		if (!name) return;
		if (strCmp(name, this->brandName)) return;

		size_t size = strLen(name);

		if (this->brandName)
		{
			delete[] brandName;
		}

		brandName = new char[size + 1];
		strCopy(name, brandName);
	}

	void setYear(int num)
	{
		if (num < GLOBAL_CONSTANTS::MIN_YEAR || num > GLOBAL_CONSTANTS::MAX_YEAR) return;

		this->year = num;
	}

	void setMaxSpeed(int num)
	{
		if (num < GLOBAL_CONSTANTS::MIN_SPEED || num > GLOBAL_CONSTANTS::MAX_SPEED) return;
		this->maxSpeed = num;
	}

	void setKilometers(const int* kilometers, int size)
	{
		if (!kilometers || size <= 0) return;

		if (this->kilometers)
		{
			delete[] this->kilometers;
		}

		this->kilometers = new int[size];
		for (int i = 0; i < size; ++i) this->kilometers[i] = kilometers[i];
		this->currentSize = size;
	}

	const char* getBrandName() const
	{
		return this->brandName;
	}

	size_t getYear() const
	{
		return this->year;
	}

	size_t getMaxSpeed()
	{
		return this->maxSpeed;
	}

	const int* getKilometers() const
	{
		return this->kilometers;
	}

	void printCar() const
	{
		std::cout << this->brandName << " " << this->year << " " << this->maxSpeed << " ";
		for (int i = 0; i < this->currentSize; ++i)
		{
			std::cout << this->kilometers[i];
		}
	}

	void writeOnFile(const char* fileName) const
	{
		if (!fileName) return;
		std::ofstream ofs(fileName);

		if (!ofs.is_open()) return;
		ofs << brandName << " ";
		ofs << year << " ";
		ofs << maxSpeed << " ";
		ofs << currentSize << " ";

		for (int i = 0; i < currentSize; ++i)
		{
			ofs << kilometers[i];
			if (i != currentSize) ofs << " ";
		}

		ofs.close();
	}

	void readFromFile(const char* fileName)
	{
		if (!fileName) return;
		std::ifstream ifs(fileName);
		if (!ifs.is_open()) return;


		ifs.close();
	}

	const size_t getKilometersSum() const
	{
		size_t sum = 0;
		for (int i = 0; i < currentSize; ++i)
		{
			sum += kilometers[i];
		}
		return sum;
	}

	const size_t getHighestRount() const
	{
		size_t highest = kilometers[0];
		for (int i = 1; i < currentSize; ++i)
		{
			if (kilometers[i] > highest) highest = kilometers[i];
		}

		return highest;
	}

	~Car()
	{
		free();
	}
};

int main()
{
	int arr[] = {1,2,3,4,5};
	Car a("Subaru", 2025, 190, arr, 5);
	
	a.printCar();
	a.readFromFile("Test7.txt");
	std::cout << a.getBrandName();

	return 0;
}
