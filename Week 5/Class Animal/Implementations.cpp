#include <iostream>
#include <fstream>
#include <cstring>
#include "Source1.h"

#pragma warning (disable : 4996);

void Animal::copyFrom(const Animal& other)
{
	this->animalName = new char[strlen(other.animalName) + 1];
	strcpy(this->animalName, other.animalName);

	this->age = other.age;
	this->animalType = other.animalType;
}

void Animal::free()
{
	delete[] this->animalName;
	this->animalName = nullptr;

	this->animalType = AnimalType::NO_TYPE;
	this->age = 0;
}

Animal::Animal()
{

}

Animal::Animal(const char* name, size_t age, const AnimalType& type)
{
	setAnimalName(name);
	setAge(age);
	setType(type);
}

Animal::Animal(const Animal& other)
{
	copyFrom(other);
}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Animal::~Animal()
{
	free();
}

void Animal::setAnimalName(const char* name)
{
	if (!name) return;

	delete[] this->animalName;
	this->animalName = new char[strlen(name) + 1];

	strcpy(this->animalName, name);
}

void Animal::setAge(size_t age)
{
	if (age <= this->age) return;

	this->age = age;
}

void Animal::setType(const AnimalType& type)
{
	this->animalType = type;
}

const char* Animal::getName() const
{
	return this->animalName;
}

size_t Animal::getAge() const
{
	return this->age;
}

const char* Animal::getType() const
{
	switch (this->animalType)
	{
	case AnimalType::MAMMAL: return CONSTANTS::MAMMAL;
	case AnimalType::REPTILE: return CONSTANTS::REPTILE;
	case AnimalType::FISH: return CONSTANTS::FISH;
	case AnimalType::BIRD: return CONSTANTS::BIRD;
	case AnimalType::AMPHIBIAN: return CONSTANTS::AMPHIBIAN;
	case AnimalType::IVERTEBRATES: return CONSTANTS::IVERTEBRATES;
	case AnimalType::INSECTS: return CONSTANTS::INSECTS;
	default: return CONSTANTS::NO_TYPE;
	}
}

int main()
{

	return 0;
}
