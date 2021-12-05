#include "lights/directional-light.h"

using namespace math;
using namespace raytracer;

namespace 
{
	class DirectionalLight : public raytracer::lights::_private_::LightSourceImplementation
	{
	public:
		DirectionalLight(const math::Vector3D& direction, const imaging::Color& color)
			: color(color), direction(direction) { }

		std::vector<LightRay> lightrays_to(const math::Point3D& point) const override
		{
			const auto f_point = Point3D(point - direction * 999);
			const auto ray = Ray(f_point, point);
			std::vector<LightRay> vector = { LightRay(ray, color) };
			return  vector;
		}
	private:
		const imaging::Color color;
		const math::Vector3D& direction;
	};
}

LightSource raytracer::lights::directional(const math::Vector3D& direction, const imaging::Color& color)
{
	return LightSource(std::make_shared<DirectionalLight>(direction, color));
}