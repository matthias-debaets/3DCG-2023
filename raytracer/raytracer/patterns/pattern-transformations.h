#pragma once

#include "patterns/pattern.h"
#include "math/transformation2d.h"
#include "math/transformation3d.h"

namespace raytracer
{
    namespace patterns
    {
        Pattern2D transform(const math::Transformation2D& transformation, Pattern2D pattern);

        Pattern2D translate(math::Vector2D displacement, Pattern2D pattern);
        Pattern2D rotate(math::Angle angle, Pattern2D pattern);
        Pattern2D scale(double sx, double sy, Pattern2D pattern);

        Pattern3D transform(const math::Transformation3D& transformation, Pattern3D pattern);

        Pattern3D translate(math::Vector3D displacement, Pattern3D pattern);
        Pattern3D rotate_x(math::Angle angle, Pattern3D pattern);
        Pattern3D rotate_y(math::Angle angle, Pattern3D pattern);
        Pattern3D rotate_z(math::Angle angle, Pattern3D pattern);
        Pattern3D scale(double sx, double sy, double sz, Pattern3D pattern);
    }
}
