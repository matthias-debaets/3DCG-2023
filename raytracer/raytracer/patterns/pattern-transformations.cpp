#include "patterns/pattern-transformations.h"
#include "lambda-pattern.h"

using namespace raytracer;
using namespace math;

namespace raytracer
{
	namespace patterns
	{
        Pattern2D transform(const Transformation2D& transformation, Pattern2D pattern)
        {
            auto function = [=](const Point2D& point) -> bool
            {
                Point2D transformed_point = transformation.inverse_transformation_matrix * point;
                return pattern(transformed_point);
            };
            return make_pattern(std::function<bool(const math::Point2D&)>(function));
        }

        Pattern2D translate(Vector2D displacement, Pattern2D pattern)
		{
			return transform(transformations::translation(displacement), pattern);
		}

        Pattern2D rotate(Angle angle, Pattern2D pattern)
        {
            return transform(transformations::rotate(angle), pattern);
        }

        Pattern2D scale(double sx, double sy, Pattern2D pattern)
		{
            return transform(transformations::scale(sx, sy), pattern);
		}

        Pattern3D transform(const Transformation3D& transformation, Pattern3D pattern)
		{
			auto function = [=](const Point3D& point) -> bool
			{
				Point3D transformed_point = transformation.inverse_transformation_matrix * point;
				return pattern(transformed_point);
			};
			return make_pattern(std::function<bool(const math::Point3D&)>(function));
		}

        Pattern3D translate(Vector3D displacement, Pattern3D pattern)
        {
	        return transform(transformations::translation(displacement), pattern);
        }

        Pattern3D rotate_x(Angle angle, Pattern3D pattern)
		{
			return transform(transformations::rotate_x(angle), pattern);
		}

        Pattern3D rotate_y(Angle angle, Pattern3D pattern)
        {
	        return transform(transformations::rotate_y(angle), pattern);
        }

        Pattern3D rotate_z(Angle angle, Pattern3D pattern)
		{
	        return transform(transformations::rotate_z(angle), pattern);
		}

		Pattern3D scale(double sx, double sy, double sz, Pattern3D pattern)
		{
	        return transform(transformations::scale(sx, sy, sz), pattern);
		}
	}
}
