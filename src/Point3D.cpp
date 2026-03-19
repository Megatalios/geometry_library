#include "geometry/Point3D.h"
#include "geometry/Vector3D.h"

// Конструктор по умолчанию
Point3D::Point3D() : x(0), y(0), z(0) {}

// Конструктор с параметрами
Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

// Конструктор копирования
Point3D::Point3D(const Point3D& otherVec) : x(otherVec.x), y(otherVec.y), z(otherVec.z) {}

// Метод для задания координат
void Point3D::setCoordinates(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// Вычитание вектора от точки
Point3D operator-(const Point3D& p, const Vector3D& v) {
	return Point3D(p.x - v.x, p.y - v.y, p.z - v.z);
}

// Сложение точки с вектором
Point3D operator+(const Point3D& p, const Vector3D& v) {
	return Point3D(p.x + v.x, p.y + v.y, p.z + v.z);
}

// Вычитание между 2 точками
Vector3D operator-(const Point3D& p1, const Point3D& p2) {
	return Vector3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

std::ostream& operator << (std::ostream& os, const Point3D& point)
{
	return os << point.x << " " << point.y << " " << point.z;
}