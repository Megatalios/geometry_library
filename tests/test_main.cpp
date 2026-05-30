#include <gtest/gtest.h>
#include <cmath>

// Подключаем все наши заголовки
#include "geometry/BasePrimitives/Point3D.h"
#include "geometry/BasePrimitives/Vector3D.h"
#include "geometry/BasePrimitives/Matrix2x2.h"
#include "geometry/BoundingBox/BoundingBox.h"
#include "geometry/Curves/LineSegment.h"
#include "geometry/Curves/BezierCurve.h"
#include "geometry/Curves/BSplineCurve.h"
#include "geometry/Surfaces/BezierSurface.h"

// ==========================================
// 1. ТЕСТЫ БАЗОВЫХ ПРИМИТИВОВ (Точки и Векторы)
// ==========================================

TEST(PointVectorTest, DistanceCalculation) {
    Point3D p1(1.0, 2.0, 3.0);
    Point3D p2(4.0, 6.0, 3.0); // Египетский треугольник 3-4-5 в плоскости XY

    Vector3D diff = p2 - p1;
    EXPECT_DOUBLE_EQ(diff.length(), 5.0);
}

TEST(PointVectorTest, VectorNormalization) {
    Vector3D v(0.0, 3.0, 4.0);
    v.normalize();

    // Длина нормализованного вектора должна быть строго равна 1
    EXPECT_DOUBLE_EQ(v.length(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 0.6); // 3 / 5
    EXPECT_DOUBLE_EQ(v.getZ(), 0.8); // 4 / 5
}


// ==========================================
// 2. ТЕСТЫ ПРОСТРАНСТВЕННОГО КЭША (AABB)
// ==========================================

TEST(BoundingBoxTest, AddPointAndExpand) {
    BoundingBox box; // Изначально пустая коробка

    // Расширяем коробку двумя крайними точками
    box.add_point(Point3D(-1.0, -2.0, -3.0));
    box.add_point(Point3D(1.0, 2.0, 3.0));
    // Добавляем точку внутри, она не должна изменить габариты
    box.add_point(Point3D(0.0, 0.0, 0.0));

    // Проверяем минимальную точку
    EXPECT_DOUBLE_EQ(box.get_min_point().getX(), -1.0);
    EXPECT_DOUBLE_EQ(box.get_min_point().getY(), -2.0);
    EXPECT_DOUBLE_EQ(box.get_min_point().getZ(), -3.0);

    // Проверяем максимальную точку
    EXPECT_DOUBLE_EQ(box.get_max_point().getX(), 1.0);
    EXPECT_DOUBLE_EQ(box.get_max_point().getY(), 2.0);
    EXPECT_DOUBLE_EQ(box.get_max_point().getZ(), 3.0);
}

TEST(BoundingBoxTest, IntersectionTrue) {
    // Коробки частично накладываются друг на друга
    BoundingBox b1(Point3D(0.0, 0.0, 0.0), Point3D(2.0, 2.0, 2.0));
    BoundingBox b2(Point3D(1.0, 1.0, 1.0), Point3D(3.0, 3.0, 3.0));

    // Пересечение должно быть найдено в обе стороны (коммутативность)
    EXPECT_TRUE(b1.is_intersect(b2));
    EXPECT_TRUE(b2.is_intersect(b1));
}

TEST(BoundingBoxTest, IntersectionFalse) {
    // Коробки находятся далеко друг от друга
    BoundingBox b1(Point3D(0.0, 0.0, 0.0), Point3D(1.0, 1.0, 1.0));
    BoundingBox b2(Point3D(5.0, 5.0, 5.0), Point3D(6.0, 6.0, 6.0));

    EXPECT_FALSE(b1.is_intersect(b2));
}

TEST(BoundingBoxTest, IntersectionEdgeCase) {
    // Коробки касаются только одной гранью (стенкой)
    BoundingBox b1(Point3D(0.0, 0.0, 0.0), Point3D(1.0, 1.0, 1.0));
    BoundingBox b2(Point3D(1.0, 0.0, 0.0), Point3D(2.0, 1.0, 1.0));

    // Касание границами тоже считается пересечением в геометрии AABB
    EXPECT_TRUE(b1.is_intersect(b2));
}
// ==========================================
// 3. ТЕСТЫ ПАРАМЕТРИЧЕСКИХ КРИВЫХ
// ==========================================

TEST(CurveTest, LineSegmentInterpolation) {
    Point3D start(0.0, 0.0, 0.0);
    Point3D end(10.0, 0.0, 0.0);
    LineSegment line(start, end);

    Point3D mid = line.get_point(0.5);
    EXPECT_DOUBLE_EQ(mid.getX(), 5.0);
    EXPECT_DOUBLE_EQ(mid.getY(), 0.0);
}

TEST(CurveTest, BezierEndpoints) {
    // Кривая Безье всегда должна строго проходить через первую и последнюю контрольную точку
    std::vector<Point3D> ctrl_points = {
        Point3D(1.0, 1.0, 1.0),
        Point3D(2.0, 5.0, 2.0),
        Point3D(4.0, -2.0, 3.0),
        Point3D(5.0, 1.0, 4.0)
    };
    BezierCurve curve(ctrl_points);

    Point3D start = curve.get_point(0.0);
    Point3D end = curve.get_point(1.0);

    EXPECT_DOUBLE_EQ(start.getX(), 1.0);
    EXPECT_DOUBLE_EQ(end.getX(), 5.0);
}

// ==========================================
// 4. ТЕСТЫ ПОВЕРХНОСТЕЙ И НОРМАЛЕЙ
// ==========================================

TEST(SurfaceTest, NormalVectorOrthogonality) {
    // Создаем простую поверхность Безье
    std::vector<std::vector<Point3D>> net = {
        { Point3D(0.0, 0.0, 0.0), Point3D(1.0, 0.0, 0.5) },
        { Point3D(0.0, 1.0, 0.0), Point3D(1.0, 1.0, 0.0) }
    };
    BezierSurface surface(net);

    double u = 0.5;
    double v = 0.5;

    // Вектор нормали должен быть строго перпендикулярен касательным Su и Sv
    Vector3D normal = surface.get_normal(u, v);
    Vector3D Su = surface.get_derivative_u(u, v);
    Vector3D Sv = surface.get_derivative_v(u, v);

    // Скалярное произведение ортогональных векторов равно нулю
    EXPECT_NEAR(normal.dot(Su), 0.0, 1e-9);
    EXPECT_NEAR(normal.dot(Sv), 0.0, 1e-9);
}

// ==========================================
// 5. ТОТ САМЫЙ ТЕСТ МЕТОДА НЬЮТОНА ИЗ ПРОШЛОГО ШАГА
// ==========================================

TEST(SurfaceTest, NewtonProjectionFlatSurface) {
    std::vector<std::vector<Point3D>> net = {
        { Point3D(0.0, 0.0, 0.0), Point3D(1.0, 0.0, 0.0) },
        { Point3D(0.0, 1.0, 0.0), Point3D(1.0, 1.0, 0.0) }
    };
    BezierSurface surface(net);

    Point3D target_point(0.5, 0.5, 5.0);
    double u = 0.0, v = 0.0;

    bool converged = surface.point_projective(target_point, u, v);

    EXPECT_TRUE(converged);
    EXPECT_NEAR(u, 0.5, 1e-5);
    EXPECT_NEAR(v, 0.5, 1e-5);
}