#pragma once
#include "geometry/Curves/ICurve.h"

class LineSegment : public ICurve {
	Point3D p1;
	Point3D p2;

	BoundingBox bbox;
	void compute_bounding_box();
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

	// Метод из интерфейса для второй производной
	Vector3D get_second_derivative(double t) const override;

	// Метод для получения проекции точки на отрезок прямой
	double point_projective(Point3D point) const override;

	// Метод для получения параллелепипеда кривой
	BoundingBox get_bounding_box() const override;

	// Перекрытие деструктора
	~LineSegment() override = default;
};