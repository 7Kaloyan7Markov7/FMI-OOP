#pragma once

namespace CONSTANTS
{
	const int CURRENT_YEAR = 2025;
	const int MAX_SIZE = 20;
	const int MAX_SHIPS = 30;
	const int MAX_WEAPONS = 100;
	const int MAX_FILE_NAME = 128;
	const char BATTLESHIP[] = "Battleship";
	const char BATTLECRUISER[] = "Battlecruiser";
	const char ERROR_MESSAGE[] = "Error";
	const char TABLE[] = "<table>";
	const char SLASH_TABLE[] = "</table>";
	const char NAME_TEMPLATE[] = "<th>Name</th>";
	const char LAUNCH_YEAR_TEMPLATE[] = "<th>Launch Year</th>";
	const char CLASS_TEMPLATE[] = "<th>Class</th>";
	const char GUNS_TEMPLATE[] = "<th>NumGuns</th>";
	const char TR[] = "<tr>";
	const char SLASH_TR[] = "</tr>";
	const char TD[] = "<td>";
	const char SLASH_TD[] = "</td>";
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
	const char* getShipType() const;
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

	int getWeaponsCount() const;

public:
	Navy() = default;
	Navy(const char* name);
	Navy(const Navy& other);
	Navy& operator=(const Navy& other);
	~Navy();

	void setName(const char* name);

	void addShip(const Ship& ship);
	void removeShip(const char* shipName);
	const Ship& getShip(size_t pos) const;
	size_t getCountOfShips() const;
	int compareNavy(const Navy& other) const;

};

class NavyHtmlTableGenerator
{
private:
	Navy navy;
	char* fileName = nullptr;

	bool validateFileName(const char* fileName) const;

	void copyFrom(const NavyHtmlTableGenerator& other);
	void free();
	
	void saveTemplate(std::ofstream& ofs) const;
	void saveNavyShips(std::ofstream& ofs) const;

public:
	NavyHtmlTableGenerator() = default;
	NavyHtmlTableGenerator(const Navy& navy, const char* fileName);
	NavyHtmlTableGenerator(const NavyHtmlTableGenerator& other);
	NavyHtmlTableGenerator& operator=(const NavyHtmlTableGenerator& other);

	void setNavy(const Navy& navy);
	void setFileName(const char* fileName);

	const Navy& getNavy() const;
	const char* getFileName() const;

	void saveToHtmlTable() const;
};
