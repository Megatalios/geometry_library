#include "geometry/Surfaces/BSplineSurface.h"

// Конструкторы
BSplineSurface::BSplineSurface() {}
BSplineSurface::BSplineSurface(const std::vector<std::vector<Point3D>>& net){}
BSplineSurface::BSplineSurface(const BSplineSurface& otherSurface){}
// Получить точку на поверхности по параметрам u, v
Point3D BSplineSurface::get_point(double u, double v) const {
	// Пока ничего не сделал
}

// Получить вектор нормали к точке с параметрами u, v
Vector3D BSplineSurface::get_normal(double u, double v) const {
	// Пока ничего не сделал
}