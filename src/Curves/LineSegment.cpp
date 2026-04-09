#include "geometry/Curves/LineSegment.h"

// Ставим по умолчанию одну и ту же точку и как начальную, и как конечную
LineSegment::LineSegment() : p1(), p2() {}

// Конструктор с параметрами
LineSegment::LineSegment(const Point3D& p1_, const Point3D& p2_) : p1(p1_), p2(p2_) {}

// Конструктор копирования
LineSegment::LineSegment(const LineSegment& other_line) : p1(other_line.p1), p2(other_line.p2) {}

// Перекрытый из интерфейса метод для получения значения точки при параметре t
Point3D LineSegment::get_point(double t) const {
	return p1 + (p2 - p1) * t;
}

// Перекрытый из интерфейса метод для получения значения производной при параметре t
Vector3D LineSegment::get_derivative(double t) const {
	return p2 - p1;
}


// Метод из интерфейса для второй производной
Vector3D LineSegment::get_second_derivative(double t) const {
	// Ускорения у отрезка прямой нет - вторые производные равны нулю
	return Vector3D(0, 0, 0);
}

// Метод для получения проекции точки на отрезок прямой
double LineSegment::point_projective(Point3D point) const {
	// Вектор направления отрезка
	Vector3D v = p2 - p1;

	// Вектор от начала отрезка до проектируемой точки
	Vector3D w = point - p1;

	// Квадрат длины вектора направления отрезка
	double v_sq_length = v.dot(v);

	// Защита от слишком малых значений
	double epsilon = 1e-9;
	if (v_sq_length < epsilon) {
		return 0.0;
	}
	// Вычисляем параметр t
	double t = w.dot(v) / v_sq_length;

	// Защита от некорректных значений t
	if (t < 0.0) return 0.0;
	if (t > 1.0) return 1.0;
	return t;

}