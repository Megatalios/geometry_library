#include "geometry/BasePrimitives/Matrix2x2.h"
#include <cmath>

// Конструкторы
Matrix2x2::Matrix2x2() : m{ {1, 0}, {0, 1} } {}
Matrix2x2::Matrix2x2(double m00, double m01, double m10, double m11) : m{ {m00, m01}, {m10, m11} } {}
Matrix2x2::Matrix2x2(const Matrix2x2& other) : m{ {other.m[0][0], other.m[0][1]}, {other.m[1][0], other.m[1][1]} } {}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const {
	return Matrix2x2(
		m[0][0] + other.m[0][0], m[0][1] + other.m[0][1],
		m[1][0] + other.m[1][0], m[1][1] + other.m[1][1]
	);
}

double Matrix2x2::det() const {
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

bool Matrix2x2::solveCramer(double b0, double b1, double& out_x, double& out_y) const {
	double determinant = Matrix2x2::det();
	if (std::abs(determinant) < 1e-9) {
		return false;
	}
	out_x = (b0 * m[1][1] - b1 * m[0][1]) / determinant;
	out_y = (m[0][0] * b1 - m[1][0] * b0) / determinant;
	return true;
}