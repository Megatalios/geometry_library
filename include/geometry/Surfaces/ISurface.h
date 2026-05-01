#include "geometry/BasePrimitives/Point3D.h"

// Интерфейс поверхности. Пока что все, что нужно нам - это нормаль и сама точка по параметрам
class ISurface {
public:
    // Получить точку на поверхности по параметрам u и v (от 0.0 до 1.0)
    virtual Point3D get_point(double u, double v) const = 0;

    // Получить вектор нормали в заданной точке (для рендера и пересечений)
    virtual Vector3D get_normal(double u, double v) const = 0;

    // Метод для получения параллелепипеда кривой
    virtual BoundingBox get_bounding_box() const = 0;

    // Виртуальный деструктор, чтобы грамотно удалялись поверхности, поддерживающие данный интерфейс
    virtual ~ISurface() = default;
};