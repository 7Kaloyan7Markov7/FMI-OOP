#include <iostream>

template <class T>
class Matrix
{
private:
	
	T** matrix;
	size_t currentSize;

	void free();
	void copyFrom(const Matrix& other);
	void moveFrom(Matrix&& other);

public:
	Matrix();
	Matrix(size_t size);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	Matrix(Matrix&& other);
	Matrix& operator=(Matrix&& other);
	~Matrix();

	void setAt(size_t x, size_t y, const T& element);

	const T& getAt(size_t x, size_t y) const;

	void transpose();
};

template <class T>
void Matrix<T>::free()
{
	if (!matrix)
	{
		currentSize = 0;
		return;
	}
	for (int i = 0; i < this->currentSize; ++i)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
	matrix = nullptr;
	currentSize = 0;
}

template <class T>
void Matrix<T>::copyFrom(const Matrix& other)
{
	this->currentSize = other.currentSize;
	matrix = new T* [other.currentSize];
	for (int i = 0; i < other.currentSize; ++i)
	{
		matrix[i] = new T[currentSize];
		for (int j = 0; j < other.currentSize; ++j)
		{
			matrix[i][j] = other.getAt(i,j);
		}
	}
}

template <class T>
void Matrix<T>::moveFrom(Matrix&& other)
{
	matrix = other.matrix;
	currentSize = other.currentSize;
	other.matrix = nullptr;
	other.currentSize = 0;
}

template <class T>
Matrix<T>::Matrix()
{
	this->currentSize = 2;

	matrix = new T* [currentSize];
	for (int i = 0; i < currentSize; ++i)
	{
		matrix[i] = new T[currentSize]{};
	}
}

template <class T>
Matrix<T>::Matrix(size_t size)
{
	this->currentSize = size;

	matrix = new T * [currentSize];
	for (int i = 0; i < currentSize; ++i)
	{
		matrix[i] = new T[currentSize]{};
	}
}

template <class T>
Matrix<T>::Matrix(const Matrix& other)
{
	copyFrom(other);
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
Matrix<T>::Matrix(Matrix&& other)
{
	moveFrom(std::move(other));
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(other);
	}

	return *this;
}

template <class T>
Matrix<T>::~Matrix()
{
	free();
}

template <class T>
void Matrix<T>::setAt(size_t x, size_t y, const T& element)
{
	if (x >= currentSize || y >= currentSize)
		throw std::out_of_range("getAt index out of bounds");

	this->matrix[x][y] = element;
}

template <class T>
const T& Matrix<T>::getAt(size_t x, size_t y) const
{
	if (x >= currentSize || y >= currentSize)
		throw std::out_of_range("setAt index out of bounds");

	return matrix[x][y];
}

template <class T>
void Matrix<T>::transpose()
{
	T** transposed = new T* [currentSize];

	for (int i = 0; i < currentSize; ++i)
	{
		transposed[i] = new T[currentSize];
		for (int j = 0; j < currentSize; ++j)
		{
			transposed[i][j] = matrix[j][i];
		}
	}

	for (int i = 0; i < currentSize; ++i)  delete[] matrix[i];
	
	delete[] matrix;
	matrix = transposed;
}		



int main()
{

	return 0;
}
