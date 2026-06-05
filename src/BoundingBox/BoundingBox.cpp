#include "geometry/BoundingBox/BoundingBox.h"

// Конструктор по умолчанию 
BoundingBox::BoundingBox(): minPoint(), maxPoint(), is_empty(false) {}

// Конструктор с параметрами
BoundingBox::BoundingBox(const Point3D& minP, const Point3D& maxP) : minPoint(minP), maxPoint(maxP), is_empty(false) {}

// Конструктор копирования
BoundingBox::BoundingBox(const BoundingBox& otherBox): minPoint(otherBox.minPoint), maxPoint(otherBox.maxPoint), is_empty(otherBox.is_empty) {}


// Метод для расширения коробки новой точкой
void BoundingBox::add_point(const Point3D& point) {
    if (is_empty) {
        minPoint = point;
        maxPoint = point;
        is_empty = false;
    }
    else {
        minPoint.setCoordinates(
            std::min(minPoint.getX(), point.getX()),
            std::min(minPoint.getY(), point.getY()),
            std::min(minPoint.getZ(), point.getZ())
        );
        maxPoint.setCoordinates(
            std::max(maxPoint.getX(), point.getX()),
            std::max(maxPoint.getY(), point.getY()),
            std::max(maxPoint.getZ(), point.getZ())
        );
    }
}

bool BoundingBox::is_intersect(const BoundingBox& other) const {
    if (is_empty || other.is_empty) return false;

    return (minPoint.getX() <= other.maxPoint.getX() && maxPoint.getX() >= other.minPoint.getX()) &&
        (minPoint.getY() <= other.maxPoint.getY() && maxPoint.getY() >= other.minPoint.getY()) &&
        (minPoint.getZ() <= other.maxPoint.getZ() && maxPoint.getZ() >= other.minPoint.getZ());
}

// Геттеры
Point3D BoundingBox::get_min_point() const {
	return minPoint;
}
Point3D BoundingBox::get_max_point() const {
	return maxPoint;
}

bool BoundingBox::contains(const BoundingBox& other) const {
    if (is_empty || other.is_empty) return false;

    return (minPoint.getX() <= other.minPoint.getX() && maxPoint.getX() >= other.maxPoint.getX() &&
        minPoint.getY() <= other.minPoint.getY() && maxPoint.getY() >= other.maxPoint.getY() &&
        minPoint.getZ() <= other.minPoint.getZ() && maxPoint.getZ() >= other.maxPoint.getZ());
}