#pragma once
#include "geometry/ICurve.h"
#include <vector>

class BSpline : public ICurve {
	std::vector<Point3D> control_points; // Контрольные точки
	std::vector<double> knot_vector; // Вектор узлов
	int degree; // Степень кривой
public:
	// Метод для получения точки кривой при заданном t
	Point3D get_point(double t) const override;

	// Метод для получения производной кривой при заданном t
	Vector3D get_derivative(double t) const override;

	// Метод для получения второй производной кривой при заданном t
	Vector3D get_second_derivative(double t) const override;

	// Проекция точки на кривую
	double point_projective(Point3D point) const override;

	// Перекрытие деструктора
	~BSpline() override = default;
};