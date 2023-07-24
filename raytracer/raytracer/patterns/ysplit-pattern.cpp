#include "ysplit-pattern.h"

using namespace raytracer;


Pattern2D patterns::ysplit(double boundary)
{
	return make_pattern([boundary](const math::Point2D& point)
		{
			return point.y() < boundary;
		});
}
