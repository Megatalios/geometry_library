#include "geometry/BasePrimitives/Point3D.h"
#include "geometry/BasePrimitives/Vector3D.h"
#include "geometry/BoundingBox/BoundingBox.h"

// Интерфейс поверхности. Пока что все, что нужно нам - это нормаль и сама точка по параметрам
class ISurface {
public:
    // Получить точку на поверхности по параметрам u и v (от 0.0 до 1.0)
    virtual Point3D get_point(double u, double v) const = 0;

    // Получить вектор нормали в заданной точке (для рендера и пересечений)
    virtual Vector3D get_normal(double u, double v) const = 0;

    // Метод для получения параллелепипеда кривой
    virtual BoundingBox get_bounding_box() const = 0;

    // Первые частные производные
    virtual Vector3D get_derivative_u(double u, double v) const = 0;
    virtual Vector3D get_derivative_v(double u, double v) const = 0;

    // Вторые частные производные
    virtual Vector3D get_second_derivative_uu(double u, double v) const = 0;
    virtual Vector3D get_second_derivative_vv(double u, double v) const = 0;

    // Смешанная частная производная
    virtual Vector3D get_second_derivative_uv(double u, double v) const = 0;

    // Многомерный метод Ньютона для проецирования точки
    // Записывает найденные параметры в out_u и out_v. Возвращает true, если сошлось.
    virtual bool point_projective(const Point3D& point, double& out_u, double& out_v) const;

    // Виртуальный деструктор, чтобы грамотно удалялись поверхности, поддерживающие данный интерфейс
    virtual ~ISurface() = default;
};