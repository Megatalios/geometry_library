#pragma once
#include "geometry/ICurve.h"
 
class LineSegment : public ICurve {
	Point3D p1;
	Point3D p2;
public:
	// Конструктор по умолчанию
	LineSegment();
 
	// Конструктор с параметрами
	LineSegment(const Point3D& p1_, const Point3D& p2_);
 
	// Конструктор копирования
	LineSegment(const LineSegment& other_line);
 
	// Метод из интерфейса для получения значения точки при параметре t
	Point3D get_point(double t) const override;
 
	// Метод из интерфейса для получения значения производной при параметре t
	Vector3D get_derivative(double t) const override;
 
	// Перекрытие деструктора
	~LineSegment() override = default;
};