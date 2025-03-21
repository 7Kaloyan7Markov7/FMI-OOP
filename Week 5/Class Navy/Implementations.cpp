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



int Navy::getWeaponsCount() const
{
	int sum = 0;
	for (int i = 0; i < currentShips; ++i)
	{
		sum += ships[i].getWeaponsCount();
	}

	return sum;
}

void Navy::copyFrom(const Navy& other)
{
	strcpy(this->countryName, other.countryName);
	this->currentShips = other.currentShips;

	for (int i = 0; i < currentShips; ++i)
	{
		this->ships[i] = other.ships[i];
	}
}

void Navy::free()
{
	currentShips = 0;
	delete[] countryName;
	countryName = nullptr;
}

Navy::Navy(const Navy& other)
{
	copyFrom(other);
}

Navy& Navy::operator=(const Navy& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Navy::~Navy()
{
	free();
}

void Navy::addShip(const Ship& ship)
{
	this->ships[currentShips] = ship;
	currentShips++;
}

void Navy::removeShip(const char* shipName)
{
	for (int i = 0; i < currentShips; ++i)
	{
		if (ships[i].getShipName())
		for (int j = i; i < currentShips - 1; ++j)
		{
			ships[i] = ships[i + 1];
		}
	}
	currentShips--;
}

const Ship& Navy::getShip(size_t pos) const
{
	return ships[pos];
}

size_t Navy::getCountOfShips() const
{
	return currentShips;
}

int Navy::compareNavy(const Navy& other) const
{
	int thisCount = this->getWeaponsCount();
	int otherCount = other.getWeaponsCount();

	if (thisCount > otherCount) return 1;
	else if (thisCount < otherCount) return -1;
	else return 0;
}


int main()
{
	Ship a("Koki", 1920, ShipType::BB, 40);
	Ship b(a);

	Navy test1;
	Navy test2;
	test1.addShip(a);
	test1.addShip(b);
	std::cout << test1.getCountOfShips();
	std::cout << test2.compareNavy(test1);
	return 0;
}
