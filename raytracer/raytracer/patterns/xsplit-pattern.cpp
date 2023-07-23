#include "xsplit-pattern.h"

using namespace raytracer;


Pattern2D patterns::xsplit(double boundary)
{
	return make_pattern([boundary](const math::Point2D& point)
	{
				return point.x() < boundary;
	});
}
