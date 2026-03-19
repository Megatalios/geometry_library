#include "geometry/Vector3D.h"
#include <cmath>
 
// Конструктор по умолчанию
Vector3D::Vector3D(): x(), y(), z() {}
 
// Конструктор с параметрами 
Vector3D::Vector3D(double x, double y, double z): x(x), y(y), z(z) {}
 
// Конструктор копирования
Vector3D::Vector3D(Vector3D& otherVec): x(otherVec.x), y(otherVec.y), z(otherVec.z) {}
 
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
 
// Сложение 2 векторов
Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
	return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
 
// Умножение вектора на число (для соблюдения коммутативности 2 вариации оператора)
Vector3D operator*(const Vector3D& v, double scalar) {
	return Vector3D(v.x * scalar, v.y * scalar, v.z * scalar);
}
Vector3D operator*(double scalar, const Vector3D& v) {
	return Vector3D(v.x * scalar, v.y * scalar, v.z * scalar);
}
 
Vector3D Vector3D::rotate(Vector3D ort, double angle) const {
	// Нормализация орта
	ort.normalize();
	// Сохранение синуса и косинуса для 
	double cosA = std::cos(angle);
	double sinA = std::sin(angle);
	// Формула Родрига
	return Vector3D((*this) * cosA + (ort).cross(*this) * sinA + ort * this->dot(ort) * (1 - cosA));
}
 
// Скалярное произведение векторов
double Vector3D::dot(const Vector3D& other) const {
	return this->x * other.x + this->y * other.y + this->z * other.z;
}
 
// Векторное произведение векторов
Vector3D Vector3D::cross(const Vector3D& other) const {
	return Vector3D(
		this->y * other.z - this->z * other.y,
		this->z * other.x - this->x * other.z,
		this->x * other.y - this->y * other.x);
}
 
// Унарный минус
Vector3D Vector3D::operator-() const {
	return Vector3D(-this->x, -this->y, -this->z);
}
 