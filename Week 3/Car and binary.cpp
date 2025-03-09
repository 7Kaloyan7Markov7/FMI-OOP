#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_NAME_SIZE = 25;
	const int MAX_TICKETS_COUNT = 20;
	const int MAX_CAR_COUNT = 10;
	const char FIRST_ROW[] = "|Brand|Owner|a/s|Tickets: {....}|";
	const char SEC_ROW[] = "|-----|-----|---|---------------|";
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
	char owner[GLOBAL_CONSTANTS::MAX_NAME_SIZE] = "No name";
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

size_t getFileSize(std::ifstream& ifs)
{
	if (!ifs.is_open()) return 0;

	size_t prevPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(prevPos);

	return size;
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
	std::cout << "|";
	printBrand(car.brand);
	std::cout << "|" << car.owner << "|" << car.averageSpeed << "|";
	printTickets(car);
	std::cout << "|" << std::endl;
}

void printCars(const Car* cars, size_t size)
{
	std::cout << GLOBAL_CONSTANTS::FIRST_ROW << std::endl;
	std::cout << GLOBAL_CONSTANTS::SEC_ROW << std::endl;
	for (int i = 0; i < size; ++i) printCar(cars[i]);
}

void writeCarInFile(const Car& car, std::ofstream& ofs)
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

void swap(Car& car1, Car& car2)
{
	Car temp = car1;
	car1 = car2;
	car2 = temp;
}

void bubbleSort(Car* cars, size_t size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (cars[j].averageSpeed > cars[j + 1].averageSpeed)
				swap(cars[j], cars[j + 1]);
		}
	}
}

void writeCar(std::ofstream& ofs,const Car& car)
{
	if (!ofs.is_open()) return;

	ofs.write((const char*)&car, sizeof(car));
}

void writeCarsInFile(std::ofstream& ofs, const Car* cars, size_t count)
{
	if (!ofs.is_open()) return;

	for (int i = 0; i < count; ++i) writeCar(ofs, cars[i]);
}

Car* readCarsFromFile(std::ifstream& ifs)
{
	if (!ifs.is_open()) return nullptr;

	size_t fileSize = getFileSize(ifs);
	size_t countOfCars = fileSize / sizeof(Car);
	Car* cars = new Car[countOfCars];

	ifs.read((char*)cars, fileSize);

	return cars;
}

int main()
{
	//test
	Car first{ Brand::SUBARU,"Koki1",3,{12,34,56},3 };
	Car sec{ Brand::PAGANI,"Koki2",2,{131,3124,56,5},4 };
	Car third{ Brand::TOYOTA,"Koki3",1,{131,124,536,5},4 };
	Car cars[3] = { first, sec, third };

	std::ofstream ofs("test7.bin", std::ios::binary);
	if (!ofs.is_open()) return -1;
	writeCarsInFile(ofs, cars, 3);

	ofs.close();

	std::ifstream ifs("test7.bin", std::ios::binary);
	if (!ifs.is_open()) return -1;
	Car* test = readCarsFromFile(ifs);

	
	ifs.close();

	printCars(cars,3);

	bubbleSort(cars, 3);
	std::cout << std::endl;
	printCars(cars, 3);

	delete[] test;
	//end of test
	return 0;
}
