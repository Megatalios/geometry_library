#pragma once
#include "geometry/Surfaces/ISurface.h"
#include "geometry/Curves/BezierCurve.h"
#include <vector>

class BezierSurface : public ISurface {
	// Матрица точек (сетка)
	std::vector<std::vector<Point3D>> control_net;
	// Для параллелепипеда поверхности
	BoundingBox bbox;

	// Вспомогательный метод для вычисления габаритов
	void compute_bounding_box();
public:
	// Конструкторы
	BezierSurface();
	BezierSurface(const std::vector<std::vector<Point3D>>& net);
	BezierSurface(const BezierSurface& otherSurface);
	// Получить точку на поверхности по параметрам u, v
	Point3D get_point(double u, double v) const override;

	// Получить вектор нормали к точке с параметрами u, v
	Vector3D get_normal(double u, double v) const override;

	// Метод для получения параллелепипеда поверхности
	BoundingBox get_bounding_box() const override;



	// Первые частные производные
	virtual Vector3D get_derivative_u(double u, double v) const override;
	virtual Vector3D get_derivative_v(double u, double v) const override;

	// Вторые частные производные
	virtual Vector3D get_second_derivative_uu(double u, double v) const override;
	virtual Vector3D get_second_derivative_vv(double u, double v) const override;

	// Смешанная частная производная
	virtual Vector3D get_second_derivative_uv(double u, double v) const override;


	// Виртуальный деструктор - нужен для корректного удаления объекта, который данный интерфейс поддерживает
	~BezierSurface() = default;
};
