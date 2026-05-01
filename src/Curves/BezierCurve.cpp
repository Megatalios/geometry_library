#include "geometry/Curves/BezierCurve.h"

// Конструкторы 
// По умолчанию
BezierCurve::BezierCurve() {}
// С параметром
BezierCurve::BezierCurve(std::vector <Point3D> control_points_) : control_points(control_points_) {}
// Копрование
BezierCurve::BezierCurve(const BezierCurve& other_curve) : control_points(other_curve.control_points) {}

// Метод для получения точки кривой при заданном t
Point3D BezierCurve::get_point(double t) const {
	int n_points = control_points.size();
	if (n_points < 1) return Point3D(0, 0, 0);
	std::vector <Point3D> temp_points = control_points;

	while (n_points > 1)
	{
		for (int i = 0; i < n_points - 1; ++i) {
			temp_points[i] = temp_points[i] + (temp_points[i + 1] - temp_points[i]) * t;
		}
		--n_points;
	}
	return temp_points[0];
}

// Метод для получения производной кривой при заданном t
Vector3D BezierCurve::get_derivative(double t) const {
	int n_points = control_points.size();
	if (n_points < 2) return Vector3D(0, 0, 0);
	int degree = n_points - 1;
	std::vector <Point3D> temp_points = control_points;
	while (n_points > 2) {
		for (int i = 0; i < n_points - 1; ++i) {
			temp_points[i] = temp_points[i] + (temp_points[i + 1] - temp_points[i]) * t;
		}
		--n_points;
	}
	return degree * (temp_points[1] - temp_points[0]);
}

// Метод для получения второй производной кривой при заданном t
Vector3D BezierCurve::get_second_derivative(double t) const {
	int n_points = control_points.size();
	if (n_points < 3) return Vector3D(0, 0, 0);
	int degree = n_points - 1;
	int scale_coef = degree * (degree - 1);
	std::vector <Point3D> temp_points = control_points;
	while (n_points > 3) {
		for (int i = 0; i < n_points - 1; ++i) {
			temp_points[i] = temp_points[i] + (temp_points[i + 1] - temp_points[i]) * t;
		}
		--n_points;
	}
	return scale_coef * ((temp_points[2] - temp_points[1]) - (temp_points[1] - temp_points[0]));
}

BoundingBox BezierCurve::get_bounding_box() const {
	// Надо что-то сделать
}