#pragma once
#include "geometry/BasePrimitives/Point3D.h"
#include <algorithm>

class BoundingBox {
private:
	Point3D minPoint;
	Point3D maxPoint;
	bool is_empty = true; // Флаг, чтобы понимать, пустая ли коробка

public:
	// Конструктор по умолчанию 
	BoundingBox();

	// Конструктор с параметрами
	BoundingBox(const Point3D& minP, const Point3D& maxP);

	// Конструктор копирования
	BoundingBox(const BoundingBox& otherBox);

	// Метод для расширения коробки новой точкой
	void add_point(const Point3D& point);

	// Геттеры
	Point3D get_min_point() const;
	Point3D get_max_point() const;

	// Проверка пересечения с другой коробкой
	bool is_intersect(const BoundingBox& other) const;
};