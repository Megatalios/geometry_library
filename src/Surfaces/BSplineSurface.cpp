#include "geometry/Surfaces/BSplineSurface.h"

// Конструкторы
BSplineSurface::BSplineSurface(const BSplineSurface& otherSurface) : 
    control_net(otherSurface.control_net), 
    degree_u(otherSurface.degree_u), 
    degree_v(otherSurface.degree_v), 
    knots_u(otherSurface.knots_u), 
    knots_v(otherSurface.knots_v) {}

// Конструктор по умолчанию
BSplineSurface::BSplineSurface() : degree_u(0), degree_v(0) {}

// Конструктор с инициализацией
BSplineSurface::BSplineSurface(
    const std::vector<std::vector<Point3D>>& net, 
    int deg_u, 
    int deg_v,
    const std::vector<double>& k_u, 
    const std::vector<double>& k_v
): control_net(net), degree_u(deg_u), degree_v(deg_v), knots_u(k_u), knots_v(k_v) {}

// Получение точки на B-сплайновой поверхности
Point3D BSplineSurface::get_point(double u, double v) const {
    if (control_net.empty() || control_net[0].empty()) {
        return Point3D(0, 0, 0);
    }

    int rows = control_net.size();
    std::vector<Point3D> temp_u_points;

    // 1. Плетем нити вдоль U (идем по строкам)
    for (int i = 0; i < rows; ++i) {
        // Создаем B-сплайн из i-той строки, используем степень и узлы для U
        BSpline temp_curve(control_net[i], degree_u, knots_u);
        temp_u_points.push_back(temp_curve.get_point(u));
    }

    // 2. Временные точки образуют поперечную нить вдоль V
    // Используем степень и узлы для V
    BSpline final_curve(temp_u_points, degree_v, knots_v);

    return final_curve.get_point(v);
}

// Получение нормали (векторное произведение касательных S_u и S_v)
Vector3D BSplineSurface::get_normal(double u, double v) const {
    if (control_net.empty() || control_net[0].empty()) {
        return Vector3D(0, 0, 1);
    }

    int rows = control_net.size();
    int cols = control_net[0].size();

    // === 1. Вектор скорости вдоль V (S_v) ===
    std::vector<Point3D> temp_u_points;
    for (int i = 0; i < rows; ++i) {
        BSpline temp_curve(control_net[i], degree_u, knots_u);
        temp_u_points.push_back(temp_curve.get_point(u));
    }
    BSpline curve_v(temp_u_points, degree_v, knots_v);
    Vector3D Sv = curve_v.get_derivative(v);


    // === 2. Вектор скорости вдоль U (S_u) ===
    std::vector<Point3D> temp_v_points;
    for (int i = 0; i < cols; ++i) {
        std::vector<Point3D> col_points;
        for (int j = 0; j < rows; ++j) {
            col_points.push_back(control_net[j][i]);
        }
        // Столбцы идут вдоль направления V, поэтому применяем параметры V
        BSpline temp_curve(col_points, degree_v, knots_v);
        temp_v_points.push_back(temp_curve.get_point(v));
    }
    // Финальная кривая идет вдоль U, применяем параметры U
    BSpline curve_u(temp_v_points, degree_u, knots_u);
    Vector3D Su = curve_u.get_derivative(u);

    // === 3. Векторное произведение ===
    Vector3D normal = Su.cross(Sv);

    if (normal.length() < 1e-9) {
        return Vector3D(0, 0, 1);
    }

    normal.normalize();
    return normal;
}

// Метод для получения параллелепипеда поверхности
BoundingBox BSplineSurface::get_bounding_box() const {

}