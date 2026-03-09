#include "geometry/Point3D.h"
#include "geometry/Vector3D.h"
#include <cmath>

// Конструктор по умолчанию
Vector3D::Vector3D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

// Конструктор с параметрами 
Vector3D::Vector3D(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// Конструктор копирования
Vector3D::Vector3D(const Vector3D& otherVec) {
	this->x = otherVec.x;
	this->y = otherVec.y;
	this->z = otherVec.z;
}

// Метод для задания координат
void Vector3D::setCoordinates(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// Вычисление длины вектора
double Vector3D::length() const {
	return sqrt(x * x + y * y + z * z);
}

// Нормализация длины вектора
void Vector3D::normalize() {
	double length = this->length();
	if (length > 0) {
		x /= length;
		y /= length;
		z /= length;
	}
}

// Скалярное произведение (возвращает число)
double Vector3D::dot(const Vector3D& other) const {
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

// Векторное произведение (возвращает новый вектор)
Vector3D Vector3D::cross(const Vector3D& other) const {
	return Vector3D(this->y * other.z - this->z * other.y, 
					this->z * other.x - this->x * other.z,
					this->x * other.y - this->y * other.x);	
}

// Сложение 2 векторов
Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
	return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// Умножение вектора на число
Vector3D operator*(const Vector3D& v, double scalar) {
	return Vector3D(v.x * scalar, v.y * scalar, v.z * scalar);
}
Vector3D operator*(double scalar, const Vector3D& v) {
	return Vector3D(v.x * scalar, v.y * scalar, v.z * scalar);
}
