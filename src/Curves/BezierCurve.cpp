#include "geometry/Curves/BezierCurve.h"

// Конструкторы 
// По умолчанию
BezierCurve::BezierCurve() {
	Point3D p1, p2;
	bbox = BoundingBox(p1, p2);
}
// С параметром
BezierCurve::BezierCurve(std::vector <Point3D> control_points_) : control_points(control_points_) {
	compute_bounding_box();
}
// Копрование
BezierCurve::BezierCurve(const BezierCurve& other_curve) : control_points(other_curve.control_points), bbox(other_curve.bbox) {}

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
	return bbox;
}

void BezierCurve::compute_bounding_box() {
	if (control_points.empty()) {
		bbox = BoundingBox(Point3D(0, 0, 0), Point3D(0, 0, 0));
		return;
	}
	Point3D minP = control_points[0];
	Point3D maxP = control_points[0];
	for (const auto& point : control_points) {
		if (point.getX() < minP.getX()) minP.setCoordinates(point.getX(), minP.getY(), minP.getZ());
		if (point.getY() < minP.getY()) minP.setCoordinates(minP.getX(), point.getY(), minP.getZ());
		if (point.getZ() < minP.getZ()) minP.setCoordinates(minP.getX(), minP.getY(), point.getZ());
		if (point.getX() > maxP.getX()) maxP.setCoordinates(point.getX(), maxP.getY(), maxP.getZ());
		if (point.getY() > maxP.getY()) maxP.setCoordinates(maxP.getX(), point.getY(), maxP.getZ());
		if (point.getZ() > maxP.getZ()) maxP.setCoordinates(maxP.getX(), maxP.getY(), point.getZ());
	}
	bbox = BoundingBox(minP, maxP);
}
