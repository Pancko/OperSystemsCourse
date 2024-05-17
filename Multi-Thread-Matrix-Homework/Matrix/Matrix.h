// ���� ���� ����� 2024
// ������� ����� ����������
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

	// ���������� ���������� �������
	void FillMatrix();

	// ����� ������� � �������
	friend std::ostream& operator<<(std::ostream&, const Matrix& Object);

	// ������������ ������ � ����� ������
	Matrix SingleThreadMultiply(const Matrix& Object);

	// ������������ ������ � ���������� �������
	Matrix MultiThreadMultiply(const Matrix& Object);

	// �������� ���� ���� ���������
	void MultOneRow(const int& Row_number, const int* Row_To_Mult, const Matrix& Matrix_To_Mult);
};

