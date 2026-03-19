#pragma once
#include <vector>
#include "geometry/ICurve.h"
 
class BezierCurve : public ICurve {
	std::vector <Point3D> control_points;
public:
	// Метод для получения точки кривой при заданном t
	Point3D get_point(double t) const override;
 
	// Метод для получения производной кривой при заданном t
	Vector3D get_derivative(double t) const override;

	Vector3D get_second_derivative(double t) const;
};