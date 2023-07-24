#include "pattern-tiling.h"

#include "lambda-pattern.h"

using namespace raytracer;
using namespace math;

namespace raytracer
{
	namespace patterns
	{
		static Point2D remap(const Point2D& point, double width, double height)
		{
			double x = std::fmod(point.x(), width);
			double y = std::fmod(point.y(), height);

			x = (x < 0) ? x + width : x;
			y = (y < 0) ? y + height : y;

			return math::Point2D(x, y);
		}

		static Point3D remap(const Point3D& point, double x_size, double y_size, double z_size)
		{
			double x = std::fmod(point.x(), x_size);
			double y = std::fmod(point.y(), y_size);
			double z = std::fmod(point.z(), z_size);

			return math::Point3D(x, y, z);
		}

		Pattern2D tiling (Pattern2D pattern, double width, double height)
		{
			auto function = [=](const Point2D& point) -> bool
			{
				const Point2D remapped_point = remap(point, width, height);
				return pattern(remapped_point);
			};
			return make_pattern(std::function<bool(const math::Point2D&)>(function));
		}

		Pattern3D tiling(Pattern3D pattern, double x_size, double y_size, double z_size)
		{
			auto function = [=](const Point3D& point) -> bool
			{
				const Point3D remapped_point = remap(point, x_size, y_size, z_size);
				return pattern(remapped_point);
			};
			return make_pattern(std::function<bool(const math::Point3D&)>(function));
		}

		Pattern2D tiling_x(Pattern2D pattern, double width)
		{
			auto function = [=](const Point2D& point) -> bool
			{
				const Point2D remapped_point = remap(point, width, 0);
				return pattern(remapped_point);
			};
			return make_pattern(std::function<bool(const math::Point2D&)>(function));
		}

		Pattern2D tiling_y(Pattern2D pattern, double height)
		{
			auto function = [=](const Point2D& point) -> bool
			{
				const Point2D remapped_point = remap(point, 0, height);
				return pattern(remapped_point);
			};
			return make_pattern(std::function<bool(const math::Point2D&)>(function));
		}
	}
}
