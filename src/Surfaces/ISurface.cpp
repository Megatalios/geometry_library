#include "geometry/Surfaces/ISurface.h"
#include "geometry/BasePrimitives/Matrix2x2.h"
#include <cmath>

// Сначала перебором находим начальное приближение, а затем уже уточняем его с помощью модифицированного метода Ньютона
bool ISurface::point_projective(const Point3D& point, double& out_u, double& out_v) const {
    //Сетка для начального приближения
    const int steps = 10;
    double min_dist_sq = 1e12;
    double best_u = 0.5, best_v = 0.5;

    // Пробегаем сетку 10x10, чтобы найти ближайшую стартовую точку
    for (int i = 0; i <= steps; ++i) {
        for (int j = 0; j <= steps; ++j) {
            double u_test = (double)i / steps;
            double v_test = (double)j / steps;
            Vector3D diff = get_point(u_test, v_test) - point;
            double dist_sq = diff.dot(diff);
            if (dist_sq < min_dist_sq) {
                min_dist_sq = dist_sq;
                best_u = u_test;
                best_v = v_test;
            }
        }
    }

    double u_cur = best_u;
    double v_cur = best_v;
    const int max_iters = 50;
    const double epsilon = 1e-6;

    // Многомерный метод Ньютона
    for (int iter = 0; iter < max_iters; ++iter) {
        Point3D S = get_point(u_cur, v_cur);
        Vector3D D = S - point; // Вектор от P до S(u,v)

        Vector3D Su = get_derivative_u(u_cur, v_cur);
        Vector3D Sv = get_derivative_v(u_cur, v_cur);

        // Значения функций, которые мы хотим обнулить (ортогональность)
        double f1 = D.dot(Su);
        double f2 = D.dot(Sv);

        // Условие выхода - обе проекции почти нулевые
        if (std::abs(f1) < epsilon && std::abs(f2) < epsilon) {
            out_u = u_cur;
            out_v = v_cur;
            return true;
        }

        // Вторые производные для Якобиана
        Vector3D Suu = get_second_derivative_uu(u_cur, v_cur);
        Vector3D Svv = get_second_derivative_vv(u_cur, v_cur);
        Vector3D Suv = get_second_derivative_uv(u_cur, v_cur);

        // Сам якобиан
        double J00 = Su.dot(Su) + D.dot(Suu);
        double J01 = Su.dot(Sv) + D.dot(Suv);
        double J10 = J01; // Матрица симметрична
        double J11 = Sv.dot(Sv) + D.dot(Svv);

        Matrix2x2 J(J00, J01, J10, J11);

        double du = 0.0, dv = 0.0;

        // Решаем J * delta = -F
        if (!J.solveCramer(-f1, -f2, du, dv)) {
            // Защита от вырождения гессиана - падаем в градиентный спуск
            du = -f1 * 0.01;
            dv = -f2 * 0.01;
        }

        // Защита от расходимости
        double alpha = 1.0;
        double u_new = u_cur, v_new = v_cur;
        double current_dist_sq = D.dot(D);

        for (int ls = 0; ls < 5; ++ls) {
            u_new = u_cur + du * alpha;
            v_new = v_cur + dv * alpha;

            // Зажимаем параметры в границах [0, 1]
            if (u_new < 0.0) u_new = 0.0; if (u_new > 1.0) u_new = 1.0;
            if (v_new < 0.0) v_new = 0.0; if (v_new > 1.0) v_new = 1.0;

            Vector3D new_D = get_point(u_new, v_new) - point;

            // Если невязка упала, значит шаг удачный — принимаем его
            if (new_D.dot(new_D) < current_dist_sq) {
                break;
            }
            // Иначе дробим шаг пополам
            alpha *= 0.5;
        }

        u_cur = u_new;
        v_cur = v_new;
    }

    out_u = u_cur;
    out_v = v_cur;
    return true; // Возвращаем результат, даже если вышли по лимиту итераций
}