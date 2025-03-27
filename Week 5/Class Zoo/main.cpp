#include <iostream>
#include <cstring>
#include <fstream>
#include "zoo_imp.h"

#pragma warning (disable: 4996)


int main()
{
	Animal a(AnimalType::AMPHIBIAN, "Joro", 3);	

	Animal b = a;
	Animal c;
	c = a;

	Zoo zoo(3, "LCS MANQCI");
	zoo.addAnimal(a);
	zoo.addAnimal(b);
	zoo.addAnimal(c);
	zoo.saveToFile("test.csv");

	return 0;
}
