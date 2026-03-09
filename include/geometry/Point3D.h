#pragma once // Защита от повторного включения
#include <cmath>

class Vector3D;


class Point3D {
private:
	double x, y, z;
public:
	// Конструктор по умолчанию
	Point3D();

	// Конструктор с параметрами
	Point3D(double x, double y, double z);

	// Конструктор копирования
	Point3D(const Point3D& otherVec);

	// Метод для задания координат
	void setCoordinates(double x, double y, double z);

	// Перегрузка операторов
	friend Point3D operator-(const Point3D& p, const Vector3D& v);

	friend Point3D operator+(const Point3D& p, const Vector3D& v);

	friend Vector3D operator-(const Point3D& p1, const Point3D& p2);
};
