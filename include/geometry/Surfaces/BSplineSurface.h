#pragma once
#include "geometry/Surfaces/ISurface.h"
#include "geometry/Curves/BSpline.h"
#include <vector>

class BSplineSurface : public ISurface {
	// Двумерная матрица контрольных точек(сетка)
	std::vector<std::vector<Point3D>> control_net;
	// Степень относительно параметрп u
	int degree_u;
	// Степень относительно параметра v
	int degree_v;

	// Узлоые точки для u и v
	std::vector<double> knots_u;
	std::vector<double> knots_v;
public:
	// Конструкторы
	BSplineSurface();
	BSplineSurface(
		const std::vector<std::vector<Point3D>>& net,
		int deg_u,
		int deg_v,
		const std::vector<double>& k_u,
		const std::vector<double>& k_v
	);
	BSplineSurface(const BSplineSurface& otherSurface);
	// Получить точку на поверхности по параметрам u, v
	Point3D get_point(double u, double v) const override;

	// Получить вектор нормали к точке с параметрами u, v
	Vector3D get_normal(double u, double v) const override;

	// Метод для получения параллелепипеда поверхности
	BoundingBox get_bounding_box() const override;

	// Виртуальный деструктор - нужен для корректного удаления объекта, который данный интерфейс поддерживает
	~BSplineSurface() = default;
};
