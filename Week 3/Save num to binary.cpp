#include <iostream>
#include <fstream>

int main()
{
	int a = 0;
	std::cin >> a;
	std::ofstream ofs("test.bin", std::ios::binary);

	if (!ofs.is_open()) return -1;

	ofs.write((const char*)&a, sizeof(int));
	ofs.close();

	return 0;
}
