#include <iostream>

struct Point
{
	int x = 0;
	int y = 0;
};

Point readPoint()
{
	int x, y;
	std::cin >> x >> y;
	return { x,y };
}

void printPoint(const Point& p)
{
	std::cout << "x is: " << p.x << std::endl;
	std::cout << "y is: " << p.y << std::endl;
}

double distance(const Point& p1, const Point& p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

struct Triangle
{
	Point A;
	Point B;
	Point C;
};

Triangle readTriangle()
{
	Triangle res;
	res.A = readPoint();
	res.B = readPoint();
	res.C = readPoint();
	return res;
}

void printTriangle(const Triangle& tri)
{
	std::cout << "A: " << std::endl;
	printPoint(tri.A);
	std::cout << "B: " << std::endl;
	printPoint(tri.B);
	std::cout << "C: " << std::endl;
	printPoint(tri.C);
}

double getPer(const double a,const double b,const double c)
{
	return a + b + c;
}

double getArea(const Triangle& tri)
{
	double a = distance(tri.B, tri.C);
	double b = distance(tri.A, tri.C);
	double c = distance(tri.A, tri.B);
	double halfPer = getPer(a, b, c) / 2;

	return sqrt(halfPer * (halfPer - a) * (halfPer - b) * (halfPer - c));
}

void printType(const Triangle& tri)
{
	double a = distance(tri.B, tri.C);
	double b = distance(tri.A, tri.C);
	double c = distance(tri.A, tri.B);

	if (a == b && b == c)
	{
		std::cout << "Triangle is equilateral";
		return;
	}

	if ((a == b && a != c) || (a == c && a != b) || b == c && b != a)
	{
		std::cout << "Triangle is isosceles";
		return;
	}
	
	std::cout << "Triangle is scalene";
}

void fillArrs(Triangle* arrTri, double* areas, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arrTri[i] = readTriangle();
		areas[i] = getArea(arrTri[i]);
	}
}

void swapTriangles(Triangle& a, Triangle& b)
{
	Triangle temp = a;
	a = b;
	b = temp;
}

void swap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}

void sortArrs(Triangle* arrTri, double* areas, int size)
{
	if (!arrTri) return;
	if (!areas) return;

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (areas[j] > areas[j + 1])
			{
				swap(areas[j], areas[j + 1]);
				swapTriangles(arrTri[j], arrTri[j + 1]);
			}
		}
	}
}

void printTriangles(Triangle* arrTri,double* areas ,int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << "Triagnle:" << std::endl;
		printTriangle(arrTri[i]);
		std::cout << "has area: " << areas[i] << std::endl;
	}
}

int main()
{
	int N = 0;
	std::cin >> N;
	if (N <= 0) return -1;

	Triangle* arrTri = new Triangle[N];
	double* areas = new double[N];
	
	fillArrs(arrTri, areas, N);
	sortArrs(arrTri, areas, N);
	printTriangles(arrTri, areas, N);

	delete[] arrTri;
	delete[] areas;
	return 0;
}
