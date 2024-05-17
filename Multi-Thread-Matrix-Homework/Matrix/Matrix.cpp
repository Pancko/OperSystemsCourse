// ТВГУ ПМиК ФИиИТ 2024
// Андреев Семен Витальевич
#include "Matrix.h"


Matrix::Matrix()
{
	rows = 0;
	columns = 0;

	matrix = new int* [rows];

	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns]();
	}
}

Matrix::Matrix(int Rows, int Columns)
{
	rows = Rows;
	columns = Columns;
	matrix = new int* [Rows];

	for (int i = 0; i < Rows; i++)
	{
		matrix[i] = new int[Columns]();
	}
}

Matrix::~Matrix()
{
	/*for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;*/
}

void Matrix::FillMatrix()
{
	int i = 0;
	for (; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = rand() % 101;
		}
	}
}

Matrix Matrix::SingleThreadMultiply(const Matrix& Object)
{
	Matrix result(this->rows, Object.columns);
	int Row = 0;
	int Column = 0;
	int temp = 0;

	for (; Row < rows; Row++)
	{
		result.MultOneRow(Row, this->matrix[Row], Object);
	}

	return result;
}

Matrix Matrix::MultiThreadMultiply(const Matrix& Object)
{
	Matrix result(this->rows, Object.columns);

	int Row = 0;

	std::vector<std::thread> thread_vector;

	for (; Row < rows; Row++)
	{
		thread_vector.push_back(std::thread(&Matrix::MultOneRow, &result, Row, this->matrix[Row], Object));
	}
	for (Row = 0; Row < rows; Row++)
		thread_vector[Row].join();

	return result;
}

void Matrix::MultOneRow(const int& Row_number, const int* Row_To_Mult, const Matrix& Matrix_To_Mult)
{
	int Column = 0;
	int Row = 0;

	for (; Column < columns; Column++)
	{
		for (Row = 0; Row < Matrix_To_Mult.rows; Row++)
			this->matrix[Row_number][Column] += Row_To_Mult[Row] * Matrix_To_Mult.matrix[Row][Column];
	}
}

std::ostream& operator<<(std::ostream&, const Matrix& Object)
{	
	int Row = 0;
	int Column = 0;

	for (Row = 0; Row < Object.rows; Row++)
	{
		std::cout << '|';
		for (Column = 0; Column < Object.columns; Column++)
		{
			std::cout << std::setw(6) << Object.matrix[Row][Column];
			if (Column != Object.columns - 1) std::cout << ';';
		}
		std::cout << '|' << std::endl;
	}
	
	return std::cout;
}
