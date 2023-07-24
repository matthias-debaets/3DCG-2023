#include "ysplit-pattern.h"

using namespace raytracer;


Pattern2D patterns::ysplit2d(double boundary)
{
	auto function = [boundary](const math::Point2D& point) -> bool
	{
		return point.y() < boundary;
	};

	return make_pattern(std::function<bool(const math::Point2D&)>(function));
}

Pattern3D patterns::ysplit3d(double boundary)
{
		auto function = [boundary](const math::Point3D& point) -> bool
		{
					return point.y() < boundary;
	};

	return make_pattern(std::function<bool(const math::Point3D&)>(function));
}
