#include "geometry/BoundingBox/BoundingBox.h"

// Конструктор по умолчанию 
BoundingBox::BoundingBox(): minPoint(), maxPoint(), is_empty(false) {}

// Конструктор с параметрами
BoundingBox::BoundingBox(const Point3D& minP, const Point3D& maxP) : minPoint(minP), maxPoint(maxP), is_empty(false) {}

// Конструктор копирования
BoundingBox::BoundingBox(const BoundingBox& otherBox): minPoint(otherBox.minPoint), maxPoint(otherBox.maxPoint), is_empty(otherBox.is_empty) {}


// Метод для расширения коробки новой точкой
void BoundingBox::add_point(const Point3D& point) {

}

// Геттеры
Point3D BoundingBox::get_min_point() const {
	return minPoint;
}
Point3D BoundingBox::get_max_point() const {
	return maxPoint;
}

// Проверка пересечения с другой коробкой
bool BoundingBox::is_intersect(const BoundingBox& other) const {

}
