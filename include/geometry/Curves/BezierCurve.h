#pragma once
#include "geometry/Curves/ICurve.h"
#include <vector>

class BezierCurve : public ICurve {
private:
	std::vector <Point3D> control_points;
	BoundingBox bbox;

	// Вспомогательный метод для вычисления габаритов
	void compute_bounding_box();
public:
	// Конструкторы 
	// По умолчанию
	BezierCurve();
	// С параметром
	BezierCurve(std::vector <Point3D> control_points_);
	// Копрование
	BezierCurve(const BezierCurve& other_curve);

	// Метод для получения точки кривой при заданном t
	Point3D get_point(double t) const override;

	// Метод для получения производной кривой при заданном t
	Vector3D get_derivative(double t) const override;

	// Метод для получения второй производной кривой при заданном t
	Vector3D get_second_derivative(double t) const override;

	// Метод для получения параллелепипеда кривой
	BoundingBox get_bounding_box() const override;

	// Перекрытие деструктора
	~BezierCurve() = default;
};