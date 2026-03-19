#pragma once
#include "Point3D.h"
#include "Vector3D.h"
 
class ICurve {
public:
	// Виртуальный деструктор для того, чтобы правильно удалялись объекты, реализиующие данный интерфейс
	virtual ~ICurve() = default;
 
	// Метод для получения точки кривой при заданном t
	virtual Point3D get_point(double t) const = 0;
 
	// Метод для получения производной кривой при заданном t
	virtual Vector3D get_derivative(double t) const = 0;
};