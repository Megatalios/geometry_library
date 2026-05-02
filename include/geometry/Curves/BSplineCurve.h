#pragma once
#include "geometry/BasePrimitives/Point3D.h"
#include "geometry/BasePrimitives/Vector3D.h"
#include "geometry/Curves/ICurve.h"
#include <vector>

class BSplineCurve : public ICurve {
	std::vector<Point3D> control_points{}; // явная инициализация по умолчанию
	int degree = 0;                         // инициализатор члена, чтобы подавить C26495
	std::vector<double> knots{};            // явная инициализация по умолчанию

	double CoxDeBoor(int i, int p, double u) const;
	std::vector<Point3D> compute_derivative_points(const std::vector<Point3D>& points, int cur_degree) const;

	BoundingBox bbox;
	// Вспомогательный метод для вычисления описанной коробки
	void compute_bounding_box();
public:
	// Конструкторы
	// По умолчанию
	BSplineCurve();
	// С параметрами
	BSplineCurve(std::vector<Point3D> initial_points, int degree, std::vector<double> initial_knots);
	// Копирования
	BSplineCurve(const BSplineCurve& other_spline);

	// Метод для получения точки кривой при заданном t
	Point3D get_point(double t) const override;

	// Метод для получения производной кривой при заданном t
	Vector3D get_derivative(double t) const override;

	Vector3D get_second_derivative(double t) const override;

	// Метод для получения параллелепипеда кривой
	BoundingBox get_bounding_box() const override;

	// Перекрытие деструктора для того, чтобы корреткно удалялись объекты, реализиующие данный интерфейс
	~BSplineCurve() = default;

};