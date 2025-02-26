#include <iostream>
#include <fstream>

size_t getCountOfNums(std::ifstream& ifs)
{
	if (!ifs.is_open()) return 0;

	size_t size = 0;
	int temp = 0;
	int prevPos = ifs.tellg();

	while (ifs >> temp) size++;

	ifs.clear();
	ifs.seekg(prevPos);
	
	return size;
}

void fillFile(const char* fileName)
{
	if (!fileName) return;

	std::ofstream ofs(fileName);
	if (!ofs.is_open()) return;

	int N, element = 0;
	std::cin >> N;

	for (int i = 0; i < N; ++i)
	{
		std::cin >> element;
		ofs << element << " ";
	}

	ofs.close();
}

void fillRes(const char* fileName, int* arr,int size)
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

int* getNums(std::ifstream& ifs, int size)
{
	int* arr = new int[size];

	for (int i = 0; i < size; ++i)
	{
		ifs >> arr[i];
	}

	return arr;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void bubbleSort(int* arr, int size, bool(*predicate)(int, int))
{
	if (!arr) return;

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (predicate(arr[j], arr[j + 1]))
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int main()
{
	fillFile("result.txt");
	std::ifstream ifs("result.txt");
	if (!ifs.is_open()) return -1;

	size_t size = getCountOfNums(ifs);
	int* arr = getNums(ifs, size);

	ifs.close();
	bool (*ascending)(int, int) = [](int a, int b) -> bool {return a > b; };
	bool (*descending)(int, int) = [](int a, int b) -> bool {return a < b; };

	bubbleSort(arr, size, ascending);
	fillRes("result1.txt", arr, size);
	bubbleSort(arr, size, descending);
	fillRes("result2.txt", arr, size);

	delete[] arr;
	return 0;
}
