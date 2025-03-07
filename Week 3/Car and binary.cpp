#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_NAME_SIZE = 25;
	const int MAX_TICKETS_COUNT = 20;
	const char FIRST_ROW[] = "|Brand|Owner|a/s|Tickets: {....}|";
	const char SEC_ROW[] =   "|-----|-----|---|---------------|";
}

enum class Brand
{
	SUBARU,
	PAGANI,
	TOYOTA,
	NOT_ASSIGNED,
};

struct Car
{
	Brand brand;
	char name[GLOBAL_CONSTANTS::MAX_NAME_SIZE] = "No name";
	double averageSpeed = 0;
	int tickets[GLOBAL_CONSTANTS::MAX_TICKETS_COUNT] = {};
	size_t currentTickets = 0;
};

Brand getCar(int num)
{
	switch (num)
	{
	case 0: return Brand::SUBARU;
		break;
	case 1: return Brand::PAGANI;
		break;
	case 2: return Brand::TOYOTA;
		break;
	default: return Brand::NOT_ASSIGNED;
		break;
	}
}

void printBrand(const Brand& brand)
{
	switch ((int)brand)
	{
	case 0: std::cout << "Subaru";
		break;
	case 1: std::cout << "Pagani";
		break;
	case 2: std::cout << "Toyota";
		break;
	default: std::cout << "Not assigned";
		break;
	}
}

void printTickets(const Car& car)
{
	std::cout << "{";
	for (int i = 0; i < car.currentTickets; ++i)
	{
		std::cout << car.tickets[i];
		if (i != car.currentTickets - 1) std::cout << ",";
	}
	std::cout << "}";
}

int getSumOfTickets(const Car& car)
{
	int sum = 0;
	for (int i = 0; i < car.currentTickets; ++i)
	{
		sum += car.tickets[i];
	}

	return sum;
}

void addTicket(Car& car)
{
	if (car.currentTickets >= GLOBAL_CONSTANTS::MAX_TICKETS_COUNT) return;
	std::cin >> car.tickets[car.currentTickets];
	car.currentTickets++;
}

void printCar(const Car& car)
{
	std::cout << GLOBAL_CONSTANTS::FIRST_ROW << std::endl;
	std::cout << GLOBAL_CONSTANTS::SEC_ROW << std::endl;
	std::cout << "|";
	printBrand(car.brand);
	std::cout << "|" << car.name << "|" << car.averageSpeed << "|";
	printTickets(car);
	std::cout << "|" << std::endl;
}

void writeCarInFile(const Car& car,std::ofstream& ofs)
{
	if (!ofs.is_open()) return;
	ofs.write((const char*)&car, sizeof(car));
}

Car readCarFromFile(std::ifstream& ifs)
{
	if (!ifs.is_open()) return {};
	Car res;

	ifs.read((char*)&res, sizeof(res));
	return res;
}

int main()
{

	return 0;
}
