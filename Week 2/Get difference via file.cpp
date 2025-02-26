#include <iostream>
#include <fstream>

void fillFile(int a,int b, int c)
{
	std::ofstream ofs("result.txt");
	if (!ofs.is_open()) return;

	int product = a * b * c;
	int sum = a + b + c;
	ofs << sum << " " << product;

	ofs.close();
}

int getDifference(const char* fileName)
{
	if (!fileName) return -1;

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return -1;

	int first, second = 0;
	ifs >> first;
	ifs >> second;
	ifs.close();

	return first - second;
}

int main()	
{
	int a, b, c = 0;
	std::cin >> a >> b >> c;

	fillFile(a, b, c);
	std::cout << getDifference("result.txt");
	return 0;
}
