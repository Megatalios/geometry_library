#pragma once
#include "Point3D.h"
#include "Vector3D.h"

// Интерфейс кривой, чтобы все кривые имели одни и те же "органы управления"
class ICurve {
public:
	// Метод для получения точки кривой при заданном t
	virtual Point3D get_point(double t) const = 0;
 
	// Метод для получения производной кривой при заданном t
	virtual Vector3D get_derivative(double t) const = 0;

	// Метод для получения второй производной кривой при заданном t
	virtual Vector3D get_second_derivative(double t) const = 0;

	// Проекция точки на кривую
	virtual double point_projective(Point3D point) const = 0;

	// Виртуальный деструктор для того, чтобы правильно удалялись объекты, реализиующие данный интерфейс
	virtual ~ICurve() = default;
};