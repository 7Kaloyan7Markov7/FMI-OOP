#pragma once

namespace constants
{
	const int MAX_AGE = 30;
}

enum class AnimalType
{
	MAMMAL,
	REPTILE,
	FISH,
	BIRD,
	AMPHIBIAN,
	IVERTEBRATES,
	INSECT,
	DEFAULT,
};

class Animal
{
private:
	AnimalType animalType = AnimalType::DEFAULT;
	char* name = nullptr;
	size_t age = 0;

	void copyFrom(const Animal& other);
	void free();

	void printType() const;

public:
	Animal() = default;
	Animal(const Animal& other);
	Animal(const AnimalType& animalType, const char* name, size_t age);
	Animal& operator=(const Animal& other);
	~Animal();

	void setName(const char* name);
	void setAge(size_t age);
	void setAnimalType(const AnimalType& animalType);

	const char* getName() const;
	size_t getAge() const;
	const AnimalType& getAnimalType() const;

	void print() const;
};
