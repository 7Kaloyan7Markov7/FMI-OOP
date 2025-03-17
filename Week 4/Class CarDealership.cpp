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
public:

	CarDealership(const Car* cars, int countOfCars)
	{
		if (!validateCount(countOfCars)) return;
		this->currentCount = countOfCars;

		for (int i = 0; i < countOfCars; ++i)
		{
			this->cars[i] = cars[i];
		}
	}

	CarDealership(const Car* cars, int countOfCars, const Engine& engine)
	{
		if (!validateCount(countOfCars)) return;
		this->currentCount = countOfCars;
		int index = 0;	
		for (int i = 0; i < countOfCars; ++i)
		{
			if(cars[i].getEngine() == engine)
			this->cars[index++] = cars[i];
		}
		this->currentCount = index - 1;
	}

	int getCurrentCount() const
	{
		return this->currentCount;
	}

	void addCar(const char* brand, const char* model, const Engine& engine, int price)
	{
		if (currentCount > CONSTANTS::MAX_CAR_COUNT) return;

		cars[currentCount] = Car(brand, model, engine, price);
		currentCount++;
	}

	void testDrive()
	{
		for (int i = 0; i < currentCount; ++i)
		{
			cars[i].drive(CONSTANTS::TEST_KILOMETER);
		}
	}
};

int main()
{

	return 0;
}
