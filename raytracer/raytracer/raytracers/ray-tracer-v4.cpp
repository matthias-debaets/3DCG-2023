#include "ray-tracer-v4.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


imaging::Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay& light_ray) const
{
    Hit new_hit;
    const auto light_hit = scene.root->find_first_positive_hit(light_ray.ray, &new_hit);
	if ( light_hit && 0.001 >= new_hit.t || new_hit.t >= 0.999)
	{
        return RayTracerV3::process_light_ray(scene, properties, hit, ray, light_ray);
	} else
	{
        return colors::black();
	}
}

raytracer::RayTracer raytracer::raytracers::v4()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}