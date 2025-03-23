#pragma once

namespace CONSTANTS
{
	const char* MAMMAL = "Mammal";
	const char* REPTILE = "Reptile";
	const char* FISH = "Fish";
	const char* BIRD = "Bird";
	const char* AMPHIBIAN = "Amphibian";
	const char* IVERTEBRATES = "Ivertebrates";
	const char* INSECTS = "Insects";
	const char* NO_TYPE = "No type";
}

enum class AnimalType
{
	MAMMAL,
	REPTILE,
	FISH,
	BIRD,
	AMPHIBIAN,
	IVERTEBRATES,
	INSECTS,
	NO_TYPE,
};


class Animal
{
private:
	AnimalType animalType = AnimalType::NO_TYPE;
	char* animalName = nullptr;
	size_t age = 0;

	void setType(const AnimalType& type);

	void copyFrom(const Animal& other);
	void free();

public:
	Animal() = default;
	Animal(const char* name, size_t age, const AnimalType& type);
	Animal(const Animal& other);
	Animal& operator=(const Animal& other);
	~Animal();

	void setAnimalName(const char* name);
	void setAge(size_t age);

	const char* getName() const;
	size_t getAge() const;
	const char* getType() const;

};
