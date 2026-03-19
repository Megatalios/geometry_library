#include "geometry/LineSegment.h"
 
// Ставим по умолчанию одну и ту же точку и как начальную, и как конечную
LineSegment::LineSegment(): p1(), p2() {}
 
// Конструктор с параметрами
LineSegment::LineSegment(const Point3D& p1_, const Point3D& p2_): p1(p1_),  p2(p2_) {}
 
// Конструктор копирования
LineSegment::LineSegment(const LineSegment& other_line): p1(other_line.p1), p2(other_line.p2) {}
 
// Перекрытый из интерфейса метод для получения значения точки при параметре t
Point3D LineSegment::get_point(double t) const {
	return p1 + (p2 - p1) * t;
}
 
// Перекрытый из интерфейса метод для получения значения производной при параметре t
Vector3D LineSegment::get_derivative(double t) const {
	return p2 - p1;
}