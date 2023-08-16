#include "math/transformation2d.h"
#include "math/transformation-matrices.h"
#include "easylogging++.h"

using namespace math;


math::Transformation2D::Transformation2D(const Matrix3x3& transformation_matrix, const Matrix3x3& inverse_transformation_matrix)
    : transformation_matrix(transformation_matrix), inverse_transformation_matrix(inverse_transformation_matrix)
{
    CHECK(transformation_matrix * inverse_transformation_matrix == approx(math::identity<3>())) << "Matrices are not each other's inverses";
}

Transformation2D math::transformations::translation(const Vector2D& v)
{
    Matrix3x3 tm = transformation_matrices::translation(v);
    Matrix3x3 itm = transformation_matrices::translation(-v);

    return Transformation2D(tm, itm);
}

Transformation2D math::transformations::rotate(Angle angle)
{
    Matrix3x3 tm = transformation_matrices::rotation(angle);
    Matrix3x3 itm = transformation_matrices::rotation(-angle);

    return Transformation2D(tm, itm);
}

Transformation2D math::transformations::scale(double sx, double sy)
{
	Matrix3x3 tm = transformation_matrices::scaling(sx, sy);
	Matrix3x3 itm = transformation_matrices::scaling(1.0 / sx, 1.0 / sy);

	return Transformation2D(tm, itm);
}
