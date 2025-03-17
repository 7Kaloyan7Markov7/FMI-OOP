#include <iostream>

namespace CONSTANTS
{
	const int MAX_NAME_SIZE = 101;
	const double COEF = 0.001;
	const int MAX_CAR_COUNT = 25;
	const char DEFAULT_BRAND[] = "No brand";
	const char DEFAULT_MODEL[] = "No model";
	const int TEST_KILOMETER = 1;
}

enum class Engine
{
	GASOLINE,
	DIESEL,
	ELECTRICITY,
	NOT_ASIGNED,
};

class Car
{
private:
	char brand[CONSTANTS::MAX_NAME_SIZE];
	char model[CONSTANTS::MAX_NAME_SIZE];
	Engine engine;
	bool isUsed;
	size_t kilometers;
	double price;

	void strCopy(const char* source, char* dest)
	{
		int index = 0;
		while (source[index] != '\0')
		{
			dest[index] = source[index];
			index++;
		}
		dest[index] = '\0';
	}

	void setBrand(const char* name)
	{
		strCopy(name, brand);
	}

	void setModel(const char* name)
	{
		strCopy(name, model);
	}

	void setEngine(const Engine& engine)
	{
		this->engine = engine;
	}

	void setPrice(double price)
	{
		this->price = price;
	}

	void printEngine() const
	{
		switch (engine)
		{
		case Engine::DIESEL: std::cout << "Engine is diesel" << std::endl;
			break;
		case Engine::GASOLINE: std::cout << "Engine is gasoline" << std::endl;
			break;
		case Engine::ELECTRICITY: std::cout << "Engine is electricity" << std::endl;
			break;
		case Engine::NOT_ASIGNED: std::cout << "Engine is not asigned" << std::endl;
			break;
		default: std::cout << "There was an error" << std::endl;
			break;
		}
	}

public:
	Car() : engine(Engine::NOT_ASIGNED), isUsed(false), kilometers(0), price(0)
	{
		strCopy(CONSTANTS::DEFAULT_BRAND, brand);
		strCopy(CONSTANTS::DEFAULT_MODEL, model);
	};

	Car(const char* brand, const char* model, const Engine& engine, int price)
	{
		setBrand(brand);
		setModel(model);
		setEngine(engine);
		setPrice(price);
	}

	void print() const
	{
		std::cout << "Brand: " << brand << std::endl;
		std::cout << "Model: " << model << std::endl;
		printEngine();
		std::cout << "Used: " << isUsed << std::endl;
		std::cout << "Price: " << price << std::endl;
	}

	void drive(int kilometers)
	{
		this->kilometers += kilometers;
		if (!isUsed) isUsed = true;

		for (int i = 0; i < kilometers; ++i)
		{
			int temp = price * CONSTANTS::COEF;
			price -= temp;
		}
	}

	const char* getBrand() const
	{
		return this->brand;
	}

	const char* getModel() const
	{
		return this->model;
	}

	const Engine getEngine() const
	{
		return this->engine;
	}

	bool getUsage() const
	{
		return this->isUsed;
	}

	size_t getKilometers() const
	{
		return this->kilometers;
	}

	double getPrice() const
	{
		return this->price;
	}
};

class CarDealership
{
private:
	Car cars[CONSTANTS::MAX_CAR_COUNT]{};
	int currentCount = 0;

	bool validateCount(int countOfCars)
	{
		if (countOfCars < 0 || countOfCars > CONSTANTS::MAX_CAR_COUNT) return false;
		return true;
	}

	int strLen(const char* str) const
	{
		if (!str) return 0;
		int index = 0;

		while (str[index] != '\0') index++;

		return  index;
	}

	bool strCmp(const char* first, const char* sec) const
	{
		int index = 0;
		int size1 = strLen(first);
		int size2 = strLen(sec);
		if (size1 != size2) return false;

		while (first[index] == sec[index] && first[index] != '\0') index++;

		if (size1 == index) return true;
		return false;
	}
public:

	CarDealership(const Car* cars, int countOfCars)
	{
		if (!validateCount(countOfCars))
		{
			this->currentCount = 0;
			return;
		};
		this->currentCount = countOfCars;

		for (int i = 0; i < countOfCars; ++i)
		{
			this->cars[i] = cars[i];
		}
	}

	CarDealership(const Car* cars, int countOfCars, const Engine& engine)
	{
		if (!validateCount(countOfCars))
		{
			this->currentCount = 0;
			return;
		}
		int index = 0;	

		for (int i = 0; i < countOfCars; ++i)
		{
			if(cars[i].getEngine() == engine)
			this->cars[index++] = cars[i];
		}
		this->currentCount = index;
	}

	CarDealership(const Car* cars, int countOfCars, const char* model)
	{
		if (!validateCount(countOfCars))
		{
			this->currentCount = 0;
			return;
		}
		int index = 0;

		for (int i = 0; i < countOfCars; ++i)
		{
			if (strCmp(cars[i].getModel(), model))
			this->cars[index++] = cars[i];
		}
		this->currentCount = index;
	}

	int getCurrentCount() const
	{
		return this->currentCount;
	}

	void addCar(const char* brand, const char* model, const Engine& engine, int price)
	{
		if (currentCount >= CONSTANTS::MAX_CAR_COUNT) return;

		this->cars[currentCount] = Car(brand, model, engine, price);
		currentCount++;
	}

	void removeCar(const char* brand, const char* model)
	{
		if (!brand || !model) return;

		for (int i = 0; i < currentCount; ++i)
		{
			if (strCmp(cars[i].getBrand(), brand) &&
				strCmp(cars[i].getModel(), model))
			{
				for (int j = i; j < currentCount - 1; ++j)
				{
					cars[j] = cars[j + 1];
				}
				currentCount -= 1;
			}
		}
	}

	void testDrive()
	{
		for (int i = 0; i < currentCount; ++i)
		{
			this->cars[i].drive(CONSTANTS::TEST_KILOMETER);
		}
	}

	void printByModel(const char* model) const
	{
		for (int i = 0; i < currentCount; ++i)
		{
			if (strCmp(model, cars[i].getModel())) cars[i].print();
		}
	}

	const Car mostExpensiveCar() const
	{
		if (!currentCount) return {};

		int highestIndex = 0;
		int highest = cars[0].getPrice();

		for (int i = 1; i < currentCount; ++i)
		{
			if (cars[i].getPrice() > highest)
			{
				highest = cars[i].getPrice();
				highestIndex = i;
			}
		}

		return cars[highestIndex];
	}

	double getAveragePrice(const Car& car) const
	{
		if (!currentCount) return 0;

		double sum = 0;
		int countOfSameBrand = 0;

		for (int i = 0; i < currentCount; ++i)
		{
			if (strCmp(cars[i].getBrand(), car.getBrand()))
			{
				countOfSameBrand++;
				sum += cars[i].getPrice();
			}
		}

		if (!countOfSameBrand) return 0;

		return sum / countOfSameBrand;
	}
};

int main()
{
	Car cars[] = {
		Car("Toyota", "Corolla", Engine::GASOLINE, 15000),
		Car("Toyota", "Camry", Engine::GASOLINE, 20000),
		Car("Toyota", "RAV4", Engine::GASOLINE, 25000),
		Car("Honda", "Civic", Engine::GASOLINE, 18000),
		Car("Honda", "Accord", Engine::GASOLINE, 22000)
	};

	return 0;
}
