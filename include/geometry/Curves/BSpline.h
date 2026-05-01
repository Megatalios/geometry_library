#include "geometry/BasePrimitives/Point3D.h"
#include "geometry/BasePrimitives/Vector3D.h"
#include "geometry/Curves/ICurve.h"
#include <vector>

class BSpline : public ICurve {
	std::vector <Point3D> control_points;
	int degree;
	std::vector <double> knots;

	double CoxDeBoor(int i, int p, double u) const;
	std::vector<Point3D> compute_derivative_points(const std::vector<Point3D>& points, int cur_degree) const;
public:
	// Конструкторы
	// По умолчанию
	BSpline();
	// С параметрами
	BSpline(std::vector<Point3D> initial_points, int degree, std::vector<double> initial_knots);
	// Копирования
	BSpline(const BSpline& other_spline);

	// Метод для получения точки кривой при заданном t
	Point3D get_point(double t) const override;

	// Метод для получения производной кривой при заданном t
	Vector3D get_derivative(double t) const override;

	Vector3D get_second_derivative(double t) const override;

	// Метод для получения параллелепипеда кривой
	BoundingBox get_bounding_box() const override;

	// Перекрытие деструктора для того, чтобы корреткно удалялись объекты, реализиующие данный интерфейс
	~BSpline() = default;

};