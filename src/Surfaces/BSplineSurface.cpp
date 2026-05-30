#include "geometry/Surfaces/BSplineSurface.h"

// Конструкторы
// по умолчанию
BSplineSurface::BSplineSurface() : degree_u(0), degree_v(0) {
    Point3D p1, p2;
	bbox = BoundingBox(p1, p2);
}

// Конструктор с параметрами
BSplineSurface::BSplineSurface(
    const std::vector<std::vector<Point3D>>& net, 
    int deg_u, 
    int deg_v,
    const std::vector<double>& k_u, 
    const std::vector<double>& k_v
): control_net(net), degree_u(deg_u), degree_v(deg_v), knots_u(k_u), knots_v(k_v) {
    compute_bounding_box();
}

// Конструктор копирования
BSplineSurface::BSplineSurface(const BSplineSurface& otherSurface) :
    control_net(otherSurface.control_net),
    degree_u(otherSurface.degree_u),
    degree_v(otherSurface.degree_v),
    knots_u(otherSurface.knots_u),
    knots_v(otherSurface.knots_v),
    bbox(otherSurface.bbox)
{}

// Получение точки на B-сплайновой поверхности
Point3D BSplineSurface::get_point(double u, double v) const {
    if (control_net.empty() || control_net[0].empty()) {
        return Point3D(0, 0, 0);
    }

    int rows = control_net.size();
    std::vector<Point3D> temp_u_points;

    // "Плетем нити" вдоль U (идем по строкам)
    for (int i = 0; i < rows; ++i) {
        // Создаем B-сплайн из i-той строки, используем степень и узлы для U
        BSplineCurve temp_curve(control_net[i], degree_u, knots_u);
        temp_u_points.push_back(temp_curve.get_point(u));
    }

    // Временные точки образуют поперечную "нить" вдоль V
    BSplineCurve final_curve(temp_u_points, degree_v, knots_v);

    return final_curve.get_point(v);
}

// Получение нормали (векторное произведение касательных S_u и S_v)
Vector3D BSplineSurface::get_normal(double u, double v) const {
    if (control_net.empty() || control_net[0].empty()) {
        return Vector3D(0, 0, 1);
    }

    int rows = control_net.size();
    int cols = control_net[0].size();

    // Вектор скорости вдоль V (S_v)
    std::vector<Point3D> temp_u_points;
    for (int i = 0; i < rows; ++i) {
        BSplineCurve temp_curve(control_net[i], degree_u, knots_u);
        temp_u_points.push_back(temp_curve.get_point(u));
    }
    BSplineCurve curve_v(temp_u_points, degree_v, knots_v);
    Vector3D Sv = curve_v.get_derivative(v);


    // Вектор скорости вдоль U (S_u) 
    std::vector<Point3D> temp_v_points;
    for (int i = 0; i < cols; ++i) {
        std::vector<Point3D> col_points;
        for (int j = 0; j < rows; ++j) {
            col_points.push_back(control_net[j][i]);
        }
        // Столбцы идут вдоль направления V, поэтому применяем параметры V
        BSplineCurve temp_curve(col_points, degree_v, knots_v);
        temp_v_points.push_back(temp_curve.get_point(v));
    }
    // Финальная кривая идет вдоль U, применяем параметры U
    BSplineCurve curve_u(temp_v_points, degree_u, knots_u);
    Vector3D Su = curve_u.get_derivative(u);

    // Векторное произведение
    Vector3D normal = Su.cross(Sv);

    if (normal.length() < 1e-9) {
        return Vector3D(0, 0, 1);
    }

    normal.normalize();
    return normal;
}

// Метод для получения параллелепипеда поверхности
BoundingBox BSplineSurface::get_bounding_box() const {
    return bbox;
}

// Вспомогательный метод для вычисления габаритов
void BSplineSurface::compute_bounding_box() {
    bbox = BoundingBox();
    for (const auto& row : control_net) {
        for (const auto& point : row) {
            bbox.add_point(point);
        }
    }
}


// Первые производные 

Vector3D BSplineSurface::get_derivative_v(double u, double v) const {
    std::vector<Point3D> temp_u_points;
    int rows = control_net.size();
    for (int i = 0; i < rows; ++i) {
        BSplineCurve temp_curve(control_net[i], degree_u, knots_u);
        temp_u_points.push_back(temp_curve.get_point(u));
    }
    BSplineCurve curve_v(temp_u_points, degree_v, knots_v);
    return curve_v.get_derivative(v);
}

Vector3D BSplineSurface::get_derivative_u(double u, double v) const {
    std::vector<Point3D> temp_v_points;
    int rows = control_net.size();
    int cols = control_net[0].size();
    for (int i = 0; i < cols; ++i) {
        std::vector<Point3D> col_points;
        for (int j = 0; j < rows; ++j) {
            col_points.push_back(control_net[j][i]);
        }
        BSplineCurve temp_curve(col_points, degree_v, knots_v);
        temp_v_points.push_back(temp_curve.get_point(v));
    }
    BSplineCurve curve_u(temp_v_points, degree_u, knots_u);
    return curve_u.get_derivative(u);
}

// Вторые чистые производные (пишутся практически так же) 

Vector3D BSplineSurface::get_second_derivative_vv(double u, double v) const {
    std::vector<Point3D> temp_u_points;
    int rows = control_net.size();
    for (int i = 0; i < rows; ++i) {
        BSplineCurve temp_curve(control_net[i], degree_u, knots_u);
        temp_u_points.push_back(temp_curve.get_point(u));
    }
    BSplineCurve curve_v(temp_u_points, degree_v, knots_v);
    // Запрашиваем вторую производную
    return curve_v.get_second_derivative(v);
}

Vector3D BSplineSurface::get_second_derivative_uu(double u, double v) const {
    std::vector<Point3D> temp_v_points;
    int rows = control_net.size();
    int cols = control_net[0].size();
    for (int i = 0; i < cols; ++i) {
        std::vector<Point3D> col_points;
        for (int j = 0; j < rows; ++j) {
            col_points.push_back(control_net[j][i]);
        }
        BSplineCurve temp_curve(col_points, degree_v, knots_v);
        temp_v_points.push_back(temp_curve.get_point(v));
    }
    BSplineCurve curve_u(temp_v_points, degree_u, knots_u);
    // Запрашиваем вторую производную
    return curve_u.get_second_derivative(u);
}

// Смешанная производная dS/du_dv

Vector3D BSplineSurface::get_second_derivative_uv(double u, double v) const {
    std::vector<Point3D> temp_u_derivs;
    int rows = control_net.size();

    // Получаем векторы скорости (производные по U) от каждой строки
    for (int i = 0; i < rows; ++i) {
        BSplineCurve temp_curve(control_net[i], degree_u, knots_u);
        Vector3D du = temp_curve.get_derivative(u);
        // превращаем вектор в точку, чтобы передать в кривую
        temp_u_derivs.push_back(Point3D(du.getX(), du.getY(), du.getZ()));
    }

    // Строим кривую в "пространстве скоростей" и берем производную по V
    BSplineCurve curve_v(temp_u_derivs, degree_v, knots_v);
    return curve_v.get_derivative(v);
}