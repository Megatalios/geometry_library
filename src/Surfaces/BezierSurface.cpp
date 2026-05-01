#include "geometry/Surfaces/BezierSurface.h"

BezierSurface::BezierSurface() {}
BezierSurface::BezierSurface(const std::vector<std::vector<Point3D>>& net) :control_net(net) {}
BezierSurface::BezierSurface(const BezierSurface& otherSurface) : control_net(otherSurface.control_net) {}

// Получить точку на поверхности по параметрам u, v
// Создаем множество кривых (по-умному - тензорное произведение)
// На каждой кривой отмечаем параметр u
// Затем из этих точек на кривых, которые получаются при параметре u, строим еще одну кривую
// На этой кривой вызываем нахождение точки v - профит 
Point3D BezierSurface::get_point(double u, double v) const {
	Point3D result(0, 0, 0);
	if (control_net.empty() || control_net[0].empty()) {
		return result;
	}
	// Сначала создаем одну кривую из точек, которая получается путем нахождения точек u в каждой созданной кривой
	int rows = control_net.size();
	std::vector<Point3D> temp_u_points;
	for (int i = 0; i < rows; ++i) {
		BezierCurve temp_curve(control_net[i]);
		temp_u_points.push_back(temp_curve.get_point(u));
	}
	// Затем в этой кривой находим уже точку с параметром v
	BezierCurve temp_v_points(temp_u_points);
	result = temp_v_points.get_point(v);

	return result;
}

// Получить вектор нормали к точке с параметрами u, v
// в этом случае для частных производных по каждому параметру 
// нужно взять сетку и по строкам, и по столбцам. 
// Таким образом мы получаем плоскость касания, которая определяется 2 векторами производных по направлениям. 
// Векторное произведение же создает еще один вектор, который ортогонален плоскости касательной
Vector3D BezierSurface::get_normal(double u, double v) const {
	if (control_net.empty() || control_net[0].empty()) {
		return Vector3D(0, 0, 1);
	}

	int rows = control_net.size();
	int cols = control_net[0].size();

	// Находим вектор скорости вдоль v (частные производные по v)
	std::vector<Point3D> temp_u_points;
	for (int i = 0; i < rows; ++i) {
		BezierCurve temp_curve(control_net[i]);
		temp_u_points.push_back(temp_curve.get_point(u));
	}
	BezierCurve curve_v(temp_u_points);
	Vector3D Sv = curve_v.get_derivative(v);

	// Находим вектор скорости вдоль u (частные производные по u)
	// Для этого идем не по строкам, а по столбцам матрицы
	std::vector<Point3D> temp_v_points;
	for (int i = 0; i < cols; ++i) {
		std::vector<Point3D> col_points;
		// Собираем i-тый столбец
		for (int j = 0; j < rows; ++j) {
			col_points.push_back(control_net[j][i]);
		}
		BezierCurve temp_curve(col_points);
		// Фиксируем v
		temp_v_points.push_back(temp_curve.get_point(v));
	}
	BezierCurve curve_u(temp_v_points);
	// Берем производную по u
	Vector3D Su = curve_u.get_derivative(u);

	// Векторное произведение
	Vector3D result = Su.cross(Sv);

	// Защита от нулевого вектора (если касательные совпали)
	if (result.length() < 1e-9) {
		return Vector3D(0, 0, 1);
	}

	// Нормализуем, чтобы вектор стал единичной длины
	result.normalize();

	return result;
}


// Метод для получения параллелепипеда поверхности
BoundingBox BezierSurface::get_bounding_box() const {

}