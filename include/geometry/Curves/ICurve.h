#pragma once
#include "geometry/BasePrimitives/Point3D.h"
#include "geometry/BasePrimitives/Vector3D.h"

class ICurve {
public:
	// Виртуальный деструктор для того, чтобы правильно удалялись объекты, реализиующие данный интерфейс
	virtual ~ICurve() = default;

	// Метод для получения точки кривой при заданном t
	virtual Point3D get_point(double t) const = 0;

	// Метод для получения производной кривой при заданном t
	virtual Vector3D get_derivative(double t) const = 0;

	// Метод для получения второй производной кривой при заданном t
	virtual Vector3D get_second_derivative(double t) const = 0;

	// Метод для получения проекции точки на кривую (не абстрактный, поскольку реализован универсальный численный метод Ньютона)
	virtual double point_projective(Point3D point) const;
};