#pragma once

#include "math/matrix.h"
#include "math/angle.h"

namespace math
{
    class Transformation2D
    {
    public:
        Transformation2D(const Matrix3x3& transformation_matrix, const Matrix3x3& inverse_transformation_matrix);

        Matrix3x3 transformation_matrix;
        Matrix3x3 inverse_transformation_matrix;
    };

    namespace transformations
    {
        Transformation2D translation(const Vector2D&);
        Transformation2D rotate(const Angle angle);
        Transformation2D scale(double sx, double sy);
    }
}
