#pragma once

namespace CONSTANTS
{
	const int CURRENT_YEAR = 2025;
	const int MAX_SIZE = 20;
	const int MAX_SHIPS = 30;
	const int MAX_WEAPONS = 100;
}

enum class ShipType
{
	BB,
	BC,
	NO_TYPE,
};

class Ship
{
private:
	char* shipName = nullptr;
	size_t year = 0;
	ShipType shipType = ShipType::NO_TYPE;
	size_t countOfWeapons = 0;

	void setYear(size_t year);

	void copyFrom(const Ship& other);
	void free();

	bool validateYear(size_t year);
	bool validateName(const char* name);
	bool validateType(const ShipType& type);
	bool validateCountOfWeapons(size_t countOfWeapons);

	void printType() const;

public:
	Ship() = default;
	Ship(const char* name, size_t year, const ShipType& shipType, size_t countOfWeapons);
	Ship(const Ship& other);
	Ship& operator=(const Ship& other);
	~Ship();

	void setShipName(const char* name);
	void setShipType(const ShipType& type);
	void setCountOfWeapons(const size_t countOfWeapons);

	const char* getShipName() const;
	const  ShipType getShipType() const;
	size_t getYear() const;
	size_t getWeaponsCount() const;

	void print() const;
};

class Navy
{
private:
	char* countryName = nullptr;
	Ship ships[CONSTANTS::MAX_SHIPS]{};
	size_t currentShips = 0;

	void copyFrom(const Navy& other);
	void free();

public:
	Navy() = default;
	Navy(const Navy& other);
	Navy& operator=(const Navy& other);
	~Navy();

	void addShip(const Ship& ship);
	void removeShip(const char* shipName);

};
