// ТВГУ ПМиК ФИиИТ 2024
// Андреев Семен Витальевич
#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>

class Matrix
{
private:
	int rows;
	int columns;
	int** matrix;

public:
	Matrix();
	Matrix(int Rows, int Columns);
	~Matrix();

	// Заполнение рандомными числами
	void FillMatrix();

	// Вывод матрицы в консоль
	friend std::ostream& operator<<(std::ostream&, const Matrix& Object);

	// Перемножение матриц в одном потоке
	Matrix SingleThreadMultiply(const Matrix& Object);

	// Перемножение матриц в нескольких потоках
	Matrix MultiThreadMultiply(const Matrix& Object);

	// Создание ряда путём умножения
	void MultOneRow(const int& Row_number, const int* Row_To_Mult, const Matrix& Matrix_To_Mult);
};

