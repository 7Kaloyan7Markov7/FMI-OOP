#include <iostream>
#include <fstream>

void fillFile(const char* fileName)
{
	if (!fileName) return;

	int N, num = 0;
	std::cin >> N;

	std::ofstream ofs(fileName);
	if (!ofs.is_open()) return;

	for (int i = 0; i < N; ++i)
	{
		std::cin >> num;
		ofs << num;
		if (i != N - 1) ofs << " ";
	}

	ofs.close();
}

size_t getCountOfNums(std::ifstream& ifs)
{
	if (!ifs.is_open()) return -1;
	size_t count = 0;
	size_t prevPos = ifs.tellg();

	int temp = 0;
	while (ifs >> temp) count++;

	ifs.clear();
	ifs.seekg(prevPos);

	return count;
}

int* getArr(std::ifstream& ifs, size_t size)
{
	if (!ifs.is_open()) return nullptr;
	size_t prevPos = ifs.tellg();


	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
	{
		ifs >> arr[i];
	}

	ifs.clear();
	ifs.seekg(prevPos);

	return arr;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void bubbleSort(int* arr, size_t size, bool(*predicate)(int, int))
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (predicate(arr[j], arr[j + 1])) swap(arr[j], arr[j + 1]);
		}
	}
}

void fillResFile(const char* fileName,int* arr, size_t size)
{
	if (!fileName) return;

	std::ofstream ofs(fileName);
	if (!ofs.is_open()) return;

	for (int i = 0; i < size; ++i)
	{
		ofs << arr[i];
		if (i != size - 1) ofs << " ";
	}

	ofs.close();
}

void fillFiles(int* arr, size_t size)
{
	bool (*ascending)(int, int) = [](int a, int b) -> bool {return a > b; };
	bool (*descending)(int, int) = [](int a, int b) -> bool {return a < b; };

	bubbleSort(arr, size, ascending);
	fillResFile("result1.txt", arr, size);
	bubbleSort(arr, size, descending);
	fillResFile("result2.txt", arr, size);
}

int main()
{
	fillFile("test.txt");
	std::ifstream ifs("test.txt");
	if (!ifs.is_open()) return -1;

	size_t size = getCountOfNums(ifs);
	int* arr = getArr(ifs,size);

	ifs.close();

	fillFiles(arr, size);

	delete[] arr;
	return 0;
}
