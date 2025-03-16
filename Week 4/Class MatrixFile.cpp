#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	const int MAX_ROWS = 30;
	const int MAX_COLS = 30;
	const int DEFAULT_VALUE = 0;
}

class MatrixFile
{
private:
	int matrix[CONSTANTS::MAX_ROWS][CONSTANTS::MAX_COLS]{};
	int currentRows = 0;
	int currentCols = 0;

	void setCurrentCols(std::ifstream& ifs)
	{
		if (!ifs.is_open()) return;

		ifs >> currentCols;
	}

	void setCurrentRows(std::ifstream& ifs)
	{
		if (!ifs.is_open()) return;

		ifs >> currentRows;
	}

	void setMatrix(std::ifstream& ifs)
	{
		if (!ifs.is_open()) return;
		for (int i = 0; i < currentRows; ++i)
		{
			for (int j = 0; j < currentCols; ++j)
			{
				ifs >> matrix[i][j];
			}
		}
	}

	void swap(int& num1, int& num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	void transposeNxM()
	{
		int tempMatrix[CONSTANTS::MAX_ROWS][CONSTANTS::MAX_COLS];
		for (int i = 0; i < currentRows; ++i)
		{
			for (int j = 0; j < currentCols; ++j)
			{
				tempMatrix[j][i] = matrix[i][j];
			}
		}

		swap(currentRows, currentCols);

		for (int i = 0; i < currentRows; ++i)
		{
			for (int j = 0; j < currentCols; ++j)
			{
				matrix[i][j] = tempMatrix[i][j];
			}
		}
	}

	void transposeNxN()
	{
		for (int i = 0; i < currentRows; ++i)
		{
			for (int j = i + 1; j < currentCols; ++j)
			{
				swap(matrix[i][j], matrix[j][i]);
			}
		}
	}

public:
	MatrixFile() : currentRows(CONSTANTS::DEFAULT_VALUE), currentCols(CONSTANTS::DEFAULT_VALUE) {};

	MatrixFile(const char* fileName)
	{
		if (!fileName) return;
		std::ifstream ifs(fileName);

		if (!ifs.is_open()) return;

		setCurrentRows(ifs);
		setCurrentCols(ifs);
		setMatrix(ifs);
		
		ifs.close();
	}

	void print() const
	{
		for (int i = 0; i < currentRows; ++i)
		{
			for (int j = 0; j < currentCols; ++j)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void transpose()
	{
		if (currentCols == currentCols) transposeNxN();
		else transposeNxM();
	}
};

int main()
{
	MatrixFile matrix("test1.txt");
	matrix.print();
	matrix.transpose();
	std::cout << std::endl;
	matrix.print();
	return 0;
}
