#include <iostream>

class BitSet
{
private:
	uint8_t* buckets = nullptr;
	size_t maxCapacity = 8;
	size_t biggestNum = 0;

	void resize(size_t capacity)
	{
		uint8_t 
	}
	
	void copyFrom(const BitSet& other)
	{

	}

	void free()
	{
		delete[] buckets;
		buckets = nullptr;
		maxCapacity = 0;
		biggestNum = 0;
	}

public:

	BitSet() = default;
	BitSet(int num)
	{
		addNumber(num);
	}
	
	void addNumber(int num)
	{

	}
};


int main()
{

	return 0;
}
