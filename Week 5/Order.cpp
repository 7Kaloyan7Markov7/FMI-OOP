#include <iostream>
#include <cstring>

namespace constants
{
	const int MAX_SIZE = 31;
	const int DEFAULT_VALUE = 0;
}

struct Item
{
	char name[constants::MAX_SIZE];
	int code;
};

class Order
{
private:
	Item* cart;
	size_t currentSize = 0;

	void copyFrom(const Order& other)
	{
		this->currentSize = other.getCurrentSize();
		cart = new Item[currentSize];

		for (int i = 0; i < currentSize; ++i)
		{
			cart[i].code = other.getItems()[i].code;
			strcpy(cart[i].name, other.getItems()[i].name);
		}
	}

	void free()
	{
		delete[] cart;
		cart = nullptr;
		currentSize = 0;
	}

public:

	Order() : cart(nullptr), currentSize(constants::DEFAULT_VALUE) {}

	void addItem()
	{

	}

	void cancel()
	{

	}

	void print() const
	{

	}

	Order(const Order& other)
	{
		free();
		copyFrom(other);
	}

	Order& operator=(const Order& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}

		return *this;
	}

	size_t getCurrentSize() const
	{
		return this->currentSize;
	}

	const Item* getItems() const
	{
		return this->cart;
	}

	~Order()
	{
		free();
	}
};


int main()
{


	return 0;
}
