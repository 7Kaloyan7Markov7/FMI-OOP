#include <iostream>
#include <stdexcept>

template <class T>
class Matrix
{
private:
	T** matrix;
	size_t rows;
	size_t cols;

	void free();
	void copyFrom(const Matrix& other);
	void moveFrom(Matrix&& other);

public:

	Matrix();
	Matrix(size_t rows, size_t cols);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);
	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other);
	~Matrix();

	void setAt(size_t row, size_t col, const T& element);
	const T& getAt(size_t row, size_t col) const;

	void print() const;
	void transpose();
};

template <class T>
void Matrix<T>::free()
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

template <class T>
void Matrix<T>::copyFrom(const Matrix& other)
{
	this->rows = other.rows;
	this->cols = other.cols;

	matrix = new T * [rows];
	for (int i = 0; i < rows; ++i)
	{
		matrix[i] = new T[cols];
		for (int j = 0; j < cols; ++j)
		{
			matrix[i][j] = other.getAt(i, j);
		}
	}
}

template <class T>
void Matrix<T>::moveFrom(Matrix&& other)
{
	this->matrix = other.matrix;
	this->rows = other.rows;
	this->cols = other.cols;
	other.matrix = nullptr;
	other.rows = 0;
	other.cols = 0;
}



template <class T>
Matrix<T>::Matrix()
{
	this->rows = 2;
	this->cols = 2;
	matrix = new T * [rows];
	for (int i = 0; i < rows; ++i)
	{
		matrix[i] = new T[cols];
	}
}

template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
	this->rows = rows;
	this->cols = cols;
	matrix = new T * [rows];
	for (int i = 0; i < rows; ++i)
	{
		matrix[i] = new T[cols];
	}
}

template <class T>
Matrix<T>::Matrix(const Matrix& other)
{
	copyFrom(other);
}

template <class T>
Matrix<T>::Matrix(Matrix&& other)
{
	moveFrom(std::move(other));
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T>
Matrix<T>::~Matrix()
{
	free();
}

template <class T>
void Matrix<T>::setAt(size_t row, size_t col, const T& element)
{
	if (row >= this->rows || col >= this->cols)
	{
		throw std::out_of_range("Matrix indices out of bounds");
	}

	matrix[row][col] = element;
}

template <class T>
const T& Matrix<T>::getAt(size_t row, size_t col) const
{
	if (row >= this->rows || col >= this->cols)
	{
		throw std::out_of_range("Matrix indices out of bounds");
	}
	return matrix[row][col];
}

template <class T>
void Matrix<T>::print() const
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			std::cout << matrix[i][j];
			if (j != cols - 1) std::cout << " ";
		}
		std::cout << std::endl;
	}
}

template <class T>
void Matrix<T>::transpose()
{
	
	T** transposed = new T * [cols];
	for (int i = 0; i < cols; ++i)
	{
		transposed[i] = new T[rows];
	} 

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			transposed[j][i] = matrix[i][j];
		}
	}

	for (int i = 0; i < rows; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	matrix = transposed;
	size_t temp = rows;
	rows = cols;
	cols = temp;
}

int main()
{
	Matrix<int> a(3,2);

	a.setAt(0, 0, 1);
	a.setAt(0, 1, 2);
	a.setAt(1, 0, 3);
	a.setAt(1, 1, 4);
	a.setAt(2, 0, 5);
	a.setAt(2, 1, 6);
	a.print();
	a.transpose();
	a.print();
}
