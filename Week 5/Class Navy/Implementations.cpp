#include <iostream>
#include <cstring>
#include "Source1.h"

#pragma warning (disable : 4996);

void Ship::copyFrom(const Ship& other)
{
	this->shipName = new char[strlen(other.shipName) + 1];
	strcpy(this->shipName, other.shipName);

	this->shipType = other.shipType;
	this->countOfWeapons = other.countOfWeapons;
	this->year = other.year;
}

void Ship::free()
{
	delete[] shipName;
	shipName = nullptr;
	countOfWeapons = 0;
	shipType = ShipType::NO_TYPE;
}

bool Ship::validateYear(size_t year)
{
	if (year > CONSTANTS::CURRENT_YEAR) return false;

	return true;
}

bool Ship::validateName(const char* name)
{
	if (!name || strlen(name) > CONSTANTS::MAX_SIZE) return false;

	return true;
}

bool Ship::validateType(const ShipType& type)
{
	switch (type)
	{
	case ShipType::BB: return true;
	case ShipType::BC: return true;
	default: return false;
	}
}

bool Ship::validateCountOfWeapons(size_t countOfWeapons)
{
	if (countOfWeapons > CONSTANTS::MAX_WEAPONS) return false;

	return true;
}

Ship::Ship(const char* name, size_t year, const ShipType& shipType, size_t countOfWeapons)
{
	setShipName(name);
	setYear(year);
	setShipType(shipType);
	setCountOfWeapons(countOfWeapons);
}

Ship::Ship(const Ship& other)
{
	copyFrom(other);
}

Ship& Ship::operator=(const Ship& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Ship::~Ship()
{
	free();
}

void Ship::setYear(size_t year)
{
	if (!validateYear(year)) return;
	this->year = year;
}

void Ship::setShipName(const char* name)
{
	if (!validateName(name)) return;

	if(this->shipName)
	delete[] this->shipName;
	this->shipName = new char[strlen(name) + 1];

	strcpy(this->shipName, name);
}

void Ship::setShipType(const ShipType& type)
{
	if (!validateType(type)) return;
	this->shipType = type;
}

void Ship::setCountOfWeapons(const size_t countOfWeapons)
{
	if (!validateCountOfWeapons(countOfWeapons)) return;
	this->countOfWeapons = countOfWeapons;
}

const char* Ship::getShipName() const
{
	return this->shipName;
}

size_t Ship::getYear() const
{
	return this->year;
}

const ShipType Ship::getShipType() const
{
	return this->shipType;
}

size_t Ship::getWeaponsCount() const
{
	return this->countOfWeapons;
}

void Ship::printType() const
{
	switch (this->shipType)
	{
	case ShipType::BB: std::cout << "battleship"; break;
	case ShipType::BC: std::cout << "battlecruiser"; break;
	default: std::cout << "Error";
	}
}

void Ship::print() const
{
	std::cout << this->shipName << "|";
	std::cout << year << "|";
	printType();
	std::cout << "|" << this->countOfWeapons;
}


int main()
{
	Ship a("Omed", 1920, ShipType::BB, 40);
	Ship b(a);

	b.print();
	return 0;
}
