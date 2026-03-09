#include "geometry/Point3D.h"
#include "geometry/Vector3D.h"

// Конструктор по умолчанию
Point3D::Point3D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

// Конструктор с параметрами
Point3D::Point3D(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// Конструктор копирования
Point3D::Point3D(const Point3D& otherVec) {
	this->x = otherVec.x;
	this->y = otherVec.y;
	this->z = otherVec.z;
}

// Метод для задания координат
void Point3D::setCoordinates(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point3D operator-(const Point3D& p, const Vector3D& v) {
	return Point3D(p.x - v.x, p.y - v.y, p.z - v.z);
}

Point3D operator+(const Point3D& p, const Vector3D& v) {
	return Point3D(p.x + v.x, p.y + v.y, p.z + v.z);
}

Vector3D operator-(const Point3D& p1, const Point3D& p2) {
	return Vector3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}
