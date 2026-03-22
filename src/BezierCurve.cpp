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


double BezierCurve::point_projective(Point3D point) const {
	// Ограничения для метода Ньютона
	const int max_iters = 100;
	// Разбиение начального отрезка для поиска начального приближения
	const int steps = 20;
	// Значение параметра t для первого приближения
	double t_best = 0.0;
	// Первое приближение минимального расстояния
   	double min_dist_sq = 1e12;
	// Число, приближенное к нулю (для проверки сходимости метода Ньютона и вырожденности гессиана)
	double epsilon = 1e-6;
   	// Поиск первого приближения
	for (int i = 0; i <= steps; ++i) {
		// Текущее значение t
		double t_step = (i * 1.0) / (max_iters * 1.0);
		// Вектор от заданной точки до точки на кривой
		Vector3D diff = get_point(t_step) - point;
		// Квадрат расстояния от заданной точки до точки на кривой
		double dist_sq = diff.dot(diff);
		if (dist_sq < min_dist_sq) {
			min_dist_sq = dist_sq;
			t_best = t_step;
		}
	}
   	double t_current = t_best;	
	//======================================	
	// Сам метод Ньютона
	for (int iter = 0; iter < max_iters; ++iter) {
		// Собираем текущую точку на кривой, первую и вторую производные
		Point3D Ct = get_point(t_current);
		Vector3D Ct_der = get_derivative(t_current);
		Vector3D Ct_sec_der = get_second_derivative(t_current);

		// Вычисляем градиент и гессиан
		Vector3D diff = Ct - point;
		double grad = diff.dot(Ct_der);
		double hess = Ct_der.dot(Ct_der) + diff.dot(Ct_sec_der);
		double current_dist_sq = diff.dot(diff);

		// Условие выхода 
		if (std::abs(grad) < epsilon) {
			break; // Достаточно близко к минимуму
		}
		double step = 0.0;
		bool is_grad_descent = false;
		if (std::abs(hess) < epsilon) {
			// Гессиан вырожден, используем градиентный спуск
			step = grad;
			is_grad_descent = true;
		} else {
			// Стандартный шаг метода Ньютона
			step = grad / hess;
		}

		// Вариативность шага
		double current_alpha = 1.0;
		double t_new = t_current;

		// Если шаг не даст уменьшения невязки, то пытаемся сделать шаг короче
		for (int ls = 0; ls < 5; ++ls) {
			// Текущий шаг
			double actual_step = current_alpha * step;
			// Случай, если градинетный спуск используется
			if (is_grad_descent) {
				// Специально небольшой шаг
				actual_step *= 0.1; 
			}
			// Пытаемся об
			t_new = t_current - actual_step;
			if (t_new < 0.0) t_new = 0.0;
			if (t_new >  1.0) t_new = 1.0;

			Point3D new_Ct = get_point(t_new);
			Vector3D new_diff = new_Ct - point;
			double new_dist_sq = new_diff.dot(new_diff);
			if (new_dist_sq < current_dist_sq) {
				break;
			}
			current_alpha *= 0.5;
		}
	}
   	//======================================

	// Защита финальная
	if (t_current < 0.0) return 0.0;
	if (t_current > 1.0) return 1.0;
	return t_current;

}