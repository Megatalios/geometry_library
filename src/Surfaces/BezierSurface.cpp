// BezierSurface.cpp
#include "geometry/Surfaces/BezierSurface.h"

BezierSurface::BezierSurface() {}
BezierSurface::BezierSurface(const std::vector<std::vector<Point3D>>& net) :control_net(net) {}
BezierSurface::BezierSurface(const BezierSurface& otherSurface) : control_net(otherSurface.control_net) {}

// Получить точку на поверхности по параметрам u, v
Point3D BezierSurface::get_point(double u, double v) const {
	Point3D result(0, 0, 0);
	if (control_net.empty() || control_net[0].empty()) {
		return result;
	}
	// Сначала создаем одну кривую из точек, которая получается путем нахождения точек u в каждой созданной кривой
	int rows = control_net.size();
	std::vector<Point3D> temp_u_points;
	for (int i = 0; i < rows; ++i) {
		BezierCurve temp_curve(control_net[i]);
		temp_u_points.push_back(temp_curve.get_point(u));
	}
	// Затем в этой кривой находим уже точку с параметром v
	BezierCurve temp_v_points(temp_u_points);
	result = temp_v_points.get_point(v);

	return result;
}

// Получить вектор нормали к точке с параметрами u, v
Vector3D BezierSurface::get_norm(double u, double v) const {
	Vector3D result(0, 0, 1);
	if (control_net.empty() || control_net[0].empty()) {
		return result;
	}
	// Что-то еще 
	return result;
}