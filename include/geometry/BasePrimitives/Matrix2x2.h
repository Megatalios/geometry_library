#pragma once
#include <iostream>

class Matrix2x2
{
	// Сама матрица
	double m[2][2];

public:
	// Конструкторы
	// По умолчанию
	Matrix2x2();
	// С параметрами (элементы передаются в виде 4 отдельных аргументов)
	Matrix2x2(double m00, double m01, double m10, double m11);
	// Конструктор копирования
	Matrix2x2(const Matrix2x2& other);

	// Операция сложения
	Matrix2x2 operator+(const Matrix2x2& other) const;

	// Вычисление определителя
	double det() const; 

	// Решение СЛАУ методом Крамера (m * x = b)
	// Возвращает true, если решение найдено (определитель не близок к нулю)
	// Результаты записываются по ссылкам в out_x и out_y
	bool solveCramer(double b0, double b1, double& out_x, double& out_y) const;

	// Функция для вывода матрицы
	friend std::ostream& operator << (std::ostream& os, const Matrix2x2& matrix);

};

