#include "ray-tracer-v6.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const Ray& eye_ray) const
{
	return trace(scene, eye_ray, 1.0);
}

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const math::Ray& eye_ray, const double weight) const
{
    Hit hit;
	if (weight < 0.01)
	{
        return TraceResult::no_hit(eye_ray);
	}

    if (scene.root->find_first_positive_hit(eye_ray, &hit))
    {

        Color hit_color = determine_color(scene, hit.material->at(hit.local_position), hit, eye_ray, weight);

        unsigned group_id = hit.group_id;

        double t = hit.t;

        return TraceResult(hit_color, group_id, eye_ray, t);
    }
    else
    {
        return TraceResult::no_hit(eye_ray);
    }
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_reflection(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    const auto reflectivity = material_properties.reflectivity;
	if (reflectivity > 0.001)
	{
        const auto reflected_ray_origin = hit.position;
        const auto reflected_ray_direction = eye_ray.direction.reflect_by(hit.normal);
        const auto reflected_ray = Ray(reflected_ray_origin + 0.0000001 * reflected_ray_direction, reflected_ray_direction );
        const auto reflected_color = trace(scene, reflected_ray, weight * reflectivity).color;
        return reflected_color * reflectivity;
	} else
	{
        return colors::black();
	}
}

imaging::Color raytracers::_private_::RayTracerV6::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, double weight) const
{
    auto result = colors::black();
    result += RayTracerV5::determine_color(scene, properties, hit, ray);
    result += compute_reflection(scene, properties, hit, ray, weight);
    return result;
}

raytracer::RayTracer raytracer::raytracers::v6()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}


