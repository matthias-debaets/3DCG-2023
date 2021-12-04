#include "raytracers/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV2::trace(const Scene& scene, const Ray& eye_ray) const
{
    Hit hit;

    // Ask the scene for the first positive hit, i.e. the closest hit in front of the eye
    // If there's a hit, find_first_positive_hit returns true and updates the hit object with information about the hit
    if (scene.root->find_first_positive_hit(eye_ray, &hit))
    {
        // There's been a hit
        // Fill in TraceResult object with information about the trace

        // This ray tracer always returns white in case of a hit
        Color hit_color = determine_color(scene, hit.material->at(hit.local_position), hit, eye_ray);

        // The hit object contains the group id, just copy it (group ids are important for edge detection)
        unsigned group_id = hit.group_id;

        // The t-value indicates where the ray/scene intersection took place.
        // You can use ray.at(t) to find the xyz-coordinates in space.
        double t = hit.t;

        // Group all this data into a TraceResult object.
        return TraceResult(hit_color, group_id, eye_ray, t);
    }
    else
    {
        // The ray missed all objects in the scene
        // Return a TraceResult object representing "no hit found"
        // which is basically the same as returning black
        return TraceResult::no_hit(eye_ray);
    }
}

imaging::Color raytracers::_private_::RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
{
    imaging::Color result = colors::black();
    for (auto &light_source : scene.light_sources)
    {
		result += process_light_source(scene, properties, hit, ray, light_source);
    }
    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightSource& light_source) const
{
    imaging::Color result = colors::black();
    for (auto &light_ray : light_source->lightrays_to(hit.position))
    {
        result += process_light_ray(scene, properties, hit, ray, light_ray);
    }
    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay light_ray) const
{
    imaging::Color result = colors::black();
    result += compute_diffuse(scene, properties, hit, ray, light_ray);
    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay light_ray) const
{
    const Vector3D n_vector = hit.normal;
    const Point3D L = light_ray.ray.origin;
    const Point3D P = hit.position;
    const Color CL = light_ray.color;
    const Color CP = properties.diffuse;

    const double cosa = (L - P).normalized().dot(n_vector);
	if (cosa > 0)
	{
        return cosa * CL * CP;
	} 
    return colors::black();
}


imaging::Color raytracers::_private_::RayTracerV2::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
{
    imaging::Color result = colors::black();
    result += RayTracerV1::determine_color(scene, properties, hit, ray);
    result += process_lights(scene, properties, hit, ray);
    return result;
}


raytracer::RayTracer raytracer::raytracers::v2()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}