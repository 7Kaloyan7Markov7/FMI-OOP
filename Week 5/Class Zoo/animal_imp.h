#pragma once
#include "animal_dec.h"
#pragma warning (disable: 4996)

void Animal::copyFrom(const Animal& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->age = other.age;
	this->animalType = other.animalType;
}

void Animal::free()
{
	delete[] this->name;
	this->name = nullptr;
	this->age = 0;
	this->animalType = AnimalType::DEFAULT;
}

Animal::Animal(const Animal& other)
{
	copyFrom(other);
}

Animal::Animal(const AnimalType& animalType, const char* name, size_t age)
{
	setName(name);
	setAnimalType(animalType);
	setAge(age);
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

void Animal::setName(const char* name)
{
	if (!name || this->name == name) return;

	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Animal::setAge(size_t age)
{
	if (age > constants::MAX_AGE) return;

	this->age = age;
}

void Animal::setAnimalType(const AnimalType& animalType)
{
	this->animalType = animalType;
}

const char* Animal::getName() const
{
	return this->name;
}

size_t Animal::getAge() const
{
	return this->age;
}

const AnimalType& Animal::getAnimalType() const
{
	return this->animalType;
}

void Animal::printType() const
{
	switch (this->animalType)
	{
	case AnimalType::MAMMAL: std::cout << "Mammal" << " "; break;
	case AnimalType::REPTILE: std::cout << "Reptile" << " "; break;
	case AnimalType::FISH: std::cout << "Fish" << " "; break;
	case AnimalType::BIRD: std::cout << "Bird" << " "; break;
	case AnimalType::AMPHIBIAN: std::cout << "Amphibian" << " "; break;
	case AnimalType::IVERTEBRATES: std::cout << "Ivertebrates" << " "; break;
	case AnimalType::INSECT: std::cout << "Insect" << " "; break;
	default: break;
	}
}

void Animal::print() const
{
	std::cout << this->name << " ";
	printType();
	std::cout << this->age << std::endl;
}
