#include "geometry/Curves/BSpline.h"

// Конструкторы
// По умолчанию
BSpline::BSpline() {}
// С параметрами
BSpline::BSpline(std::vector<Point3D> initial_points, int degree_, std::vector<double> initial_knots) : control_points(initial_points), degree(degree_), knots(initial_knots) {}
// Копирования
BSpline::BSpline(const BSpline& other_spline) : control_points(other_spline.control_points), degree(other_spline.degree), knots(other_spline.knots) {}

// Метод для получения точки кривой при заданном t
Point3D BSpline::get_point(double t) const {
	Point3D result(0, 0, 0);
	int control_points_size = control_points.size();
	for (int i = 0; i < control_points_size; ++i) {
		double weight = CoxDeBoor(i, degree, t);
		result.setCoordinates(
			result.getX() + control_points[i].getX() * weight,
			result.getY() + control_points[i].getY() * weight,
			result.getZ() + control_points[i].getZ() * weight);
	}
	return result;
}

// Метод для получения производной кривой при заданном t
Vector3D BSpline::get_derivative(double t) const {
	// Получаем контрольные точки для кривой скоростей
	std::vector<Point3D> q_points = compute_derivative_points(control_points, degree);
	double q_points_size = q_points.size();
	double vx = 0, vy = 0, vz = 0;
	// В основном цикле суммирование с весами Кокса, Де Бура
	for (int i = 0; i < q_points_size; ++i) {
		// Степень снижается
		double weight = CoxDeBoor(i, degree - 1, t);

		vx += q_points[i].getX() * weight;
		vy += q_points[i].getY() * weight;
		vz += q_points[i].getZ() * weight;
	}
	// Возвращаем вектор касательной
	return Vector3D(vx, vy, vz);
}

Vector3D BSpline::get_second_derivative(double t) const {
	// Защита на случай, если степень меньше 2
	if (degree < 2) {
		return Vector3D(0, 0, 0);
	}
	// Получаем контрольные точки для кривой скоростей
	std::vector<Point3D> q_points = compute_derivative_points(control_points, degree);
	double q_points_size = q_points.size();

	// Получаем контрольные точки для кривой ускорений
	std::vector<Point3D> w_points = compute_derivative_points(q_points, degree - 1);
	double w_points_size = w_points.size();
	double ax = 0, ay = 0, az = 0;
	for (int i = 0; i < w_points_size; ++i) {
		// Степень снижается
		double weight = CoxDeBoor(i, degree - 2, t);
		ax += w_points[i].getX() * weight;
		ay += w_points[i].getY() * weight;
		az += w_points[i].getZ() * weight;
	}
	return Vector3D(ax, ay, az);

}

double BSpline::CoxDeBoor(int i, int p, double u) const {
	// Базовый случай (степень равна 0)
	// Функция равна 1, если параметр u находится внутри текущего интервала узла
	if (p == 0) {
		if (knots[i] <= u && u < knots[i + 1]) {
			return 1.0;
		}
		return 0.0;
	}
	// Рекурсивный случай (степень p > 0)
	double left = 0.0;
	double right = 0.0;

	// Левая дробь
	double denom_left = knots[i + p] - knots[i];
	if (denom_left != 0.0) {
		left = ((u - knots[i]) / denom_left) * CoxDeBoor(i, p - 1, u);
	}

	// Поавая дробь
	double denom_right = knots[i + p + 1] - knots[i + 1];
	if (denom_right != 0.0) {
		right = ((knots[i + p + 1] - u) / denom_right) * CoxDeBoor(i + 1, p - 1, u);
	}

	return left + right;
}

std::vector <double> generate_clamped_points(int num_points, int degree) {
	// Количество узлов = количество точек + степень + 1
	int num_knots = num_points + degree + 1;

	// Сам вектор для хранения узлов
	std::vector <double> knots(num_knots);

	// Количество отрезков, на которые делятся узлы
	int num_segments = num_points - degree;

	// Заполняем узлы по логике краевых условий
	for (int i = 0; i < num_knots; ++i) {
		// Первые (степень + 1) узлов ставим в 0
		if (i <= degree) {
			knots[i] = 0.0;
		}
		else {
			// Последние (степень + 1) узлов ставим в 1
			if (i >= num_points) {
				knots[i] = 1.0;
			}
			// Осталььные - по вот этой формуле
			else {
				knots[i] = 1.0 * (i - degree) / num_segments;
			}
		}
	}
	return knots;
}


std::vector<Point3D> BSpline::compute_derivative_points(const std::vector<Point3D>& points, int cur_degree) const {
	std::vector<Point3D> q_points;
	// Количество точек
	int points_size = points.size();

	// Защита, если точек мало или степень нулевая
	if (points_size <= 1 || cur_degree < 1) return q_points;

	// Точек производной на 1 меньше
	q_points.resize(points_size - 1);

	//Основной цикл
	for (int i = 0; i < points_size; ++i) {
		// Знаменатель формулы B-сплайна
		double denom = knots[i + cur_degree + 1] - knots[i + 1];
		Point3D q;


		if (denom != 0.0) {
			double coef = cur_degree / denom;
			// Разница между соседними точками (вектор скорости, как я понял)
			double dx = (points[i + 1].getX() - points[i].getX()) * coef;
			double dy = (points[i + 1].getY() - points[i].getY()) * coef;
			double dz = (points[i + 1].getZ() - points[i].getZ()) * coef;

			q.setCoordinates(dx, dy, dz);
		}
		else {
			// Если же знаменатель равен нулю, то точки совпали, вектор скорости равен 0
			q.setCoordinates(0, 0, 0);
		}
		q_points[i] = q;
	}
	return q_points;
}


BoundingBox BSpline::get_bounding_box() const {
	// Надо что-то сделать
}