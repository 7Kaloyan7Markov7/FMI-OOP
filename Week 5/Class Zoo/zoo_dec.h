#pragma once
#include "animal_imp.h"

class Zoo
{
private:
	char* name = nullptr;
	Animal*  animals = nullptr;
	size_t maxCapacity = 0;
	size_t currentSize = 0;

	void copyFrom(const Zoo& other);
	void free();

	void setName(const char* name);
	void setCapacity(size_t maxCapacity);
	void saveTypeToFile(std::ofstream& ofs, const AnimalType& type) const;

public:
	Zoo() = default;
	Zoo(size_t maxCapacity,const char* name);
	Zoo(const Zoo& other);
	Zoo& operator=(const Zoo& other);
	~Zoo();

	void addAnimal(const Animal& animal);
	void removeAnimal(const char* name);
	size_t getCountOfType(const AnimalType& type) const;
	void print() const;
	void saveToFile(const char* fileName) const;

};
