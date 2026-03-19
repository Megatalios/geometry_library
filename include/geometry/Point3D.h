#pragma once
#include <iostream>
 
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
 
	// Из точки вычитаем вектор
	friend Point3D operator-(const Point3D& p, const Vector3D& v);
 
	// К точке прибавляем вектор
	friend Point3D operator+(const Point3D& p, const Vector3D& v);
 
	// Оператор вывода для точки
	friend std::ostream& operator << (std::ostream& os, const Point3D& point);
 
	// Из точки вычитаем точку
	friend Vector3D operator-(const Point3D& p1, const Point3D& p2);
};