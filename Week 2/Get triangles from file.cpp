#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int MAX_BUFF_SIZE = 1024;
}

struct Point
{
	int x;
	int y;
};

struct Triangle
{
	Point A;
	Point B;
	Point C;
};

void fillArr(Point* arr,size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cin >> arr[i].x >> arr[i].y;
	}
}

size_t getCounOfLines(std::ifstream& ifs)
{
	if (!ifs.is_open()) return 0;
	size_t prevPos = ifs.tellg();
	size_t counter = 0;
	char buff[GLOBAL_CONSTANTS::MAX_BUFF_SIZE];

	while (!ifs.eof())
	{
		ifs.getline(buff, GLOBAL_CONSTANTS::MAX_BUFF_SIZE);
		counter++;
	}

	ifs.clear();
	ifs.seekg(prevPos);
	
	return counter - 1;
}

void writeInFile(const char* fileName,Point* arr, size_t size)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open()) return;

	for (size_t i = 0; i < size; ++i)
	{
		ofs << arr[i].x << " " << arr[i].y << "\n";
	}

	ofs.close();
}

Triangle* readTriangleFromFile(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return nullptr;

	size_t size = getCounOfLines(ifs);
	Triangle* resArr = new Triangle[size / 3];

	for (size_t i = 0; i < size / 3; ++i)
	{
		ifs >> resArr[i].A.x >> resArr[i].A.y;
		ifs >> resArr[i].B.x >> resArr[i].B.y;
		ifs >> resArr[i].C.x >> resArr[i].C.y;
	}

	ifs.close();
	return resArr;
}

void printPoint(const Point& p)
{
	std::cout << "(" << p.x << "," << p.y << ") ";
}

void printTriangle(const Triangle& tri)
{
	printPoint(tri.A);
	printPoint(tri.B);
	printPoint(tri.C);
	std::cout << std::endl;
}

int main()
{
	size_t size = 0;
	std::cin >> size;

	Point* arr = new Point[size];
	fillArr(arr, size);
	writeInFile("test.txt", arr, size);
	Triangle* triArr = readTriangleFromFile("test.txt");

	for (int i = 0; i < size / 3; ++i)
	{
		std::cout << "Triangle " << i + 1 << ": ";
		printTriangle(triArr[i]);
	}

	delete[] triArr;
	delete[] arr;
}
