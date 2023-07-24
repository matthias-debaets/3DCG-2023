#include "xsplit-pattern.h"

using namespace raytracer;


Pattern2D patterns::xsplit2d(double boundary)
{
	auto function = [boundary](const math::Point2D& point) -> bool
	{
				return point.x() < boundary;
	};

	return make_pattern(std::function<bool(const math::Point2D&)>(function));
}

Pattern3D patterns::xsplit3d(double boundary)
{
		auto function = [boundary](const math::Point3D& point) -> bool
		{
					return point.x() < boundary;
	};

	return make_pattern(std::function<bool(const math::Point3D&)>(function));
}
