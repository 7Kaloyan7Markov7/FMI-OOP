#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	const int MAX_ROWS = 30;
	const int MAX_COLS = 30;
	const int DEFAULT_VALUE = 0;
	const int MAX_FILENAME_LEN = 65;
}

class MatrixFile
{
private:
	int matrix[CONSTANTS::MAX_ROWS][CONSTANTS::MAX_COLS]{};
	int currentRows = 0;
	int currentCols = 0;
	char fileName[CONSTANTS::MAX_FILENAME_LEN] = "";

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

	void strCopy(const char* source, char* dest)
	{
		int index = 0;
		while (source[index] != '\0')
		{
			dest[index] = source[index];
			index++;
		}
		dest[index] = '\0';
	}

	void saveMatrix(std::ofstream& ofs) const
	{
		if (!ofs.is_open()) return;

		for (int i = 0; i < currentRows; ++i)
		{
			for (int j = 0; j < currentCols; ++j)
			{
				ofs << matrix[i][j];
				if (j != currentCols - 1) ofs << " ";
			}
			if(i != currentRows - 1) ofs << "\n";
		}
	}

	void saveRowsAndCols(std::ofstream& ofs) const
	{
		if (!ofs.is_open()) return;
		ofs << currentRows << " ";
		ofs << currentCols << "\n";
	}

public:
	MatrixFile() : currentRows(CONSTANTS::DEFAULT_VALUE), currentCols(CONSTANTS::DEFAULT_VALUE) {};

	MatrixFile(const char* fileName)
	{
		if (!fileName) return;
		std::ifstream ifs(fileName);

		if (!ifs.is_open()) return;

		setFileName(fileName);
		setCurrentRows(ifs);
		setCurrentCols(ifs);
		setMatrix(ifs);
		
		ifs.close();
	}

	void setFileName(const char* fileName)
	{
		if (!fileName) return;
		strCopy(fileName, this->fileName);
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

	void multiplyByNum(int num)
	{
		for (int i = 0; i < currentRows; ++i)
		{
			for (int j = 0; j < currentCols; ++j)
			{
				matrix[i][j] *= num;
			}
		}
	}

	void changeElement(int i, int j, int input)
	{
		if (i < 0 || i > currentRows) return;
		if (j < 0 || j > currentCols) return;

		matrix[i][j] = input;
	}
	
	void saveMatrixToFile(const char* fileName) const
	{
		if (!fileName) return;
		std::ofstream ofs(fileName);

		if (!ofs.is_open()) return;
		saveRowsAndCols(ofs);
		saveMatrix(ofs);

		ofs.close();
	}

	~MatrixFile()
	{
		saveMatrixToFile(this->fileName);
	}
};

int main()
{
	
	return 0;
}
