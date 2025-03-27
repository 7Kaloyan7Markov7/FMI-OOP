#pragma once
#include "zoo_dec.h"
#pragma warning (disable: 4996)

void Zoo::copyFrom(const Zoo& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->currentSize = other.currentSize;

	this->maxCapacity = other.maxCapacity;
	this->animals = new Animal[other.maxCapacity];
	for (int i = 0; i < currentSize; ++i)
	{
		this->animals[i] = other.animals[i];
	}
}
void Zoo::free()
{
	delete[] this->animals;
	this->animals = nullptr;
	delete[] this->name;
	this->name = nullptr;
	this -> maxCapacity = 0;
	this->currentSize = 0;
}

void Zoo::setName(const char* name)
{
	if (!name || this->name == name) return;

	delete[] this->name;
	
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Zoo::setCapacity(size_t maxCapacity)
{
	this->maxCapacity = maxCapacity;
}

Zoo::Zoo(size_t maxCapacity, const char* name)
{
	setName(name);
	setCapacity(maxCapacity);
	
	this->animals = new Animal[this->maxCapacity]{};
}

Zoo::Zoo(const Zoo& other)
{
	copyFrom(other);
}

Zoo& Zoo::operator=(const Zoo& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Zoo::~Zoo()
{
	free();
}

void Zoo::addAnimal(const Animal& animal)
{
	if (this->currentSize >= this->maxCapacity) return;

	this->animals[currentSize] = animal;
	currentSize++;
}

void Zoo::removeAnimal(const char* name)
{
	if (!currentSize) return;

	for (int i = 0; i < this->currentSize; ++i)
	{
		if (!strcmp(this->animals[i].getName(), name))
		{
			for (int j = i; j < this->currentSize - 1; ++j)
			{
				this->animals[j] = this->animals[j + 1];
			}
			--this->currentSize;
		}
	}
}

size_t Zoo::getCountOfType(const AnimalType& type) const
{
	size_t res = 0;
	for (int i = 0; i < currentSize; ++i)
	{
		if ((int)this->animals[i].getAnimalType() == (int)type) res++;
	}

	return res;
}

void Zoo::print() const
{
	for (int i = 0; i < currentSize; ++i)
	{
		std::cout << "Animal number " << i + 1 << ": ";
		this->animals[i].print();
	}
}

void Zoo::saveTypeToFile(std::ofstream& ofs, const AnimalType& type) const
{
	switch (type)
	{
	case AnimalType::MAMMAL: ofs << "Mammal" << ","; break;
	case AnimalType::REPTILE: ofs << "Reptile" << ","; break;
	case AnimalType::FISH: ofs << "Fish" << ","; break;
	case AnimalType::BIRD: ofs << "Bird" << ","; break;
	case AnimalType::AMPHIBIAN: ofs << "Amphibian" << ","; break;
	case AnimalType::IVERTEBRATES: ofs << "Ivertebrates" << ","; break;
	case AnimalType::INSECT: ofs << "Insect" << ","; break;
	default: break;
	}
}

void Zoo::saveToFile(const char* fileName) const
{
	if (!fileName) return;

	std::ofstream ofs(fileName);
	if (!ofs.is_open()) return;
	for (int i = 0; i < currentSize; ++i)
	{
		ofs << animals[i].getName() << ",";
		saveTypeToFile(ofs, animals[i].getAnimalType());
		ofs << animals[i].getAge();
		if(i != currentSize - 1) ofs << "\n";
	}

	ofs.close();
}
