#include <iostream>
#include <fstream>
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

const char* Ship::getShipType() const
{
	switch (this->shipType)
	{
	case ShipType::BB: return CONSTANTS::BATTLESHIP;
	case ShipType::BC: return CONSTANTS::BATTLECRUISER;
	default: return CONSTANTS::ERROR_MESSAGE;
	}
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
	this->countryName = new char[strlen(other.countryName) + 1];

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

Navy::Navy(const char* name)
{
	setName(name);
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

void Navy::setName(const char* name)
{
	if (!name) return;

	delete[] this->countryName;
	this->countryName = new char[strlen(name) + 1];

	strcpy(this->countryName, name);
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



bool NavyHtmlTableGenerator::validateFileName(const char* fileName) const
{
	return fileName;
}

void NavyHtmlTableGenerator::copyFrom(const NavyHtmlTableGenerator& other)
{
	this->navy = other.navy;

	fileName = new char[strlen(other.fileName) + 1];
	strcpy(fileName, other.fileName);
}

void NavyHtmlTableGenerator::free()
{
	delete[] fileName;
	fileName = nullptr;
}

NavyHtmlTableGenerator::NavyHtmlTableGenerator(const Navy& navy, const char* fileName)
{
	setNavy(navy);
	setFileName(fileName);
}

NavyHtmlTableGenerator::NavyHtmlTableGenerator(const NavyHtmlTableGenerator& other)
{
	copyFrom(other);
}

NavyHtmlTableGenerator& NavyHtmlTableGenerator::operator=(const NavyHtmlTableGenerator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

void NavyHtmlTableGenerator::setNavy(const Navy& navy)
{
	this->navy = navy;
}

void NavyHtmlTableGenerator::setFileName(const char* fileName)
{
	if (!validateFileName(fileName)) return;

	delete[] this->fileName;
	this->fileName = new char[strlen(fileName) + 1];

	strcpy(this->fileName, fileName);
}

const Navy& NavyHtmlTableGenerator::getNavy() const
{
	return this->navy;
}

const char* NavyHtmlTableGenerator::getFileName() const
{
	return this->fileName;
}

void NavyHtmlTableGenerator::saveTemplate(std::ofstream& ofs) const
{
	ofs << "\t\t" << CONSTANTS::NAME_TEMPLATE << "\n";
	ofs << "\t\t" << CONSTANTS::LAUNCH_YEAR_TEMPLATE << "\n";
	ofs << "\t\t" << CONSTANTS::CLASS_TEMPLATE << "\n";
	ofs << "\t\t" << CONSTANTS::GUNS_TEMPLATE << "\n";
}

void NavyHtmlTableGenerator::saveNavyShips(std::ofstream& ofs) const
{
	int size = navy.getCountOfShips();

	for (int i = 0; i < size; ++i)
	{
		Ship temp = navy.getShip(i);
		ofs << "\t" << CONSTANTS::TR << "\n";
		ofs << "\t\t" << CONSTANTS::TD << "Ship " << i + 1 << " " << temp.getShipName() << CONSTANTS::SLASH_TD << "\n";
		ofs << "\t\t" << CONSTANTS::TD << "Ship " << i + 1 << " " << temp.getYear() << CONSTANTS::SLASH_TD << "\n";
		ofs << "\t\t" << CONSTANTS::TD << "Ship " << i + 1 << " " << temp.getShipType() << CONSTANTS::SLASH_TD << "\n";
		ofs << "\t\t" << CONSTANTS::TD << "Ship " << i + 1 << " " << temp.getWeaponsCount() << CONSTANTS::SLASH_TD << "\n";
		ofs << "\t" << CONSTANTS::SLASH_TR << "\n";
	}
}

void NavyHtmlTableGenerator::saveToHtmlTable() const
{
	std::ofstream ofs(this->fileName);
	if (!ofs.is_open()) return;

	ofs << CONSTANTS::TABLE << "\n" << "\t" << CONSTANTS::TR << "\n";
	saveTemplate(ofs);
	ofs << "\t" << CONSTANTS::SLASH_TR << "\n";
	saveNavyShips(ofs);
	ofs << CONSTANTS::SLASH_TABLE;

	ofs.close();
}

int main()
{
	Ship ship1("Black Pearl",341, ShipType::BB, 30);
	Ship ship2("Silent death", 1891, ShipType::BB, 38);
	Ship ship3("Vin Dieasel", 2014, ShipType::BC, 0);

	Navy navy("mashite");
	navy.addShip(ship1);
	navy.addShip(ship2);
	navy.addShip(ship3);

	NavyHtmlTableGenerator generator(navy, "test1.txt");
	generator.saveToHtmlTable();
	
	return 0;
}
