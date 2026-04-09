#pragma once
#include <iostream>

class Point3D;

class Vector3D {
private:
	double x, y, z;
public:
	// Конструктор по умолчанию
	Vector3D();

	// Конструктор с параметрами
	Vector3D(double x, double y, double z);

	// Конструктор копирования
	Vector3D(Vector3D& otherVec);

	// Метод для задания координат
	void setCoordinates(double x, double y, double z);

	// Длина вектора
	double length() const;

	// Нормализация длины вектора
	void normalize();

	// Векторное произведение векторов
	Vector3D cross(const Vector3D& other) const;

	// Скалярное произведение векторов
	double dot(const Vector3D& other) const;

	// Унарный минус
	Vector3D operator-() const;

	// Из точки вычитаем вектор
	friend Point3D operator-(const Point3D& p, const Vector3D& v);

	// К точке прибавляем вектор
	friend Point3D operator+(const Point3D& p, const Vector3D& v);

	// Сложение 2 векторов
	friend Vector3D operator+(const Vector3D& v1, const Vector3D& v2);

	// Умножение вектора на скаляр
	friend Vector3D operator*(const Vector3D& v, double scalar);
	friend Vector3D operator*(double scalar, const Vector3D& v);

	// Вычитание векторов
	friend Vector3D operator-(const Vector3D& first, const Vector3D& second);

	friend std::ostream& operator << (std::ostream& os, const Vector3D& vec);

	// Поворот вектора с помощью формулы Родрига
	Vector3D rotate(Vector3D ort, double angle) const;
};