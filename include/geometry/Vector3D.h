#pragma once // Защита от повторного включения

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
	Vector3D(const Vector3D& otherVec);

	// Метод для задания координат
	void setCoordinates(double x, double y, double z);

	// Длина вектора
	double length() const;

	void normalize();

	// Скалярное произведение (возвращает число)
	double dot(const Vector3D& other) const;

	// Векторное произведение (возвращает новый вектор)
	Vector3D cross(const Vector3D& other) const;

	friend Point3D operator-(const Point3D& p, const Vector3D& v);

	friend Point3D operator+(const Point3D& p, const Vector3D& v);

	friend Vector3D operator+(const Vector3D& v1, const Vector3D& v2);

	friend Vector3D operator*(const Vector3D& v, double scalar);
	friend Vector3D operator*(double scalar, const Vector3D& v);
};