#include "materials/pattern-material.h"
#include "materials/composition-material.h"

using namespace raytracer;

Material materials::pattern2d(const Pattern2D& pattern, const Material& m1, const Material& m2)
{
    auto function = [pattern, m1, m2](const math::Point2D& point) -> Material
    {
        return pattern(point) ? m1 : m2;
    };

    return composite(std::function<Material(const math::Point2D&)>(function));
}

Material materials::pattern3d(const Pattern3D& pattern, const Material& m1, const Material& m2)
{
	auto function = [pattern, m1, m2](const math::Point3D& point) -> Material
	{
		return pattern(point) ? m1 : m2;
	};

	return composite(std::function<Material(const math::Point3D&)>(function));
}