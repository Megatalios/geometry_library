#include "geometry/BezierCurve.h"

// Метод для получения точки кривой при заданном t
Point3D BezierCurve::get_point(double t) const {
	if (control_points.empty()) {
		// В идеале тут бросать исключение, но пока можно вернуть точку в нуле
		return Point3D(0, 0, 0);
	}
	// Промежуточные точки для алгоритма Де Кастельжо (копируем, поскольку не хотим менять внутреннее состояние)
	std::vector <Point3D> temp_points = control_points;
	// Переменная-ограничитель для итеративного вычисления точки
	int n_points = temp_points.size();
	// Итеративный процесс вычисления точки
	while (n_points > 1) {
		for (int i = 0; i < n_points - 1; ++i) {
			// Формула точки на прямой между соседними точками
			temp_points[i] = temp_points[i] + (temp_points[i + 1] - temp_points[i]) * t;
		}
		--n_points;
	}
	return temp_points[0];
}

// Метод  для получения производной кривой при заданном t
Vector3D BezierCurve::get_derivative(double t) const {
	if (control_points.size() < 2) {
		return Vector3D(0, 0, 0); // У точки нет скорости
	}
	// Промежуточные точки для алгоритма Де Кастельжо (копируем, поскольку не хотим менять внутреннее состояние)
	std::vector <Point3D> temp_points = control_points;
	// Переменная-ограничитель для итеративного вычисления точки
	int n_points = temp_points.size();
	// Степень кривой
	int degree = n_points - 1;
	// Сам итеративный процесс вычисления точки
	while (n_points > 2) {
		for (int i = 0; i < n_points - 1; ++i) {
			// Формула точки на прямой между соседними точками
			temp_points[i] = temp_points[i] + (temp_points[i + 1] - temp_points[i]) * t;
		}
		--n_points;
	}
	return degree * (temp_points[1] - temp_points[0]);
}

Vector3D BezierCurve::get_second_derivative(double t) const {
	if (control_points.size() < 2) {
		return Vector3D(0, 0, 0); // У точки нет скорости
	}
	// Промежуточные точки для алгоритма Де Кастельжо (копируем, поскольку не хотим менять внутреннее состояние)
	std::vector <Point3D> temp_points = control_points;
	// Переменная-ограничитель для итеративного вычисления точки
	int n_points = temp_points.size();
	// Степень кривой
	int degree = n_points - 1;
	// Коэффициент, на которую нужно домножать вторую производную
	double scale = degree * (degree - 1);
	// Сам итеративный процесс вычисления точки
	while (n_points > 3) {
		for (int i = 0; i < n_points - 1; ++i) {
			// Формула точки на прямой между соседними точками
			temp_points[i] = temp_points[i] + (temp_points[i + 1] - temp_points[i]) * t;
		}
		--n_points;
	}
	return scale * ((temp_points[1] - temp_points[0]) + (temp_points[2] - temp_points[1]));
}