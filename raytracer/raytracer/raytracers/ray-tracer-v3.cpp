#include "ray-tracer-v3.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV3::trace(const Scene& scene, const Ray& eye_ray) const
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

imaging::Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const
{
    Vector3D n_vector = hit.normal;
	Point3D L = light_ray.ray.origin;
    Point3D P = hit.position;
    Point3D E = light_ray.ray.at(0);
    Color CL = light_ray.color;
    Color CP = properties.specular;
    double e = properties.specular_exponent;

    Vector3D i = (P - L).normalized();
    Vector3D r = i -  2*(i.dot(n_vector))*n_vector;
    Vector3D v = (E - P).normalized();
    double cosa = v.dot(r);
    if (cosa > 0)
    {
        return CL * CP * pow(cosa, e);
    }
    else
    {
        return colors::black();
    }
}

imaging::Color raytracer::raytracers::_private_::RayTracerV3::process_light_ray(const Scene & scene, const MaterialProperties & properties, const Hit & hit, const math::Ray & ray, LightRay light_ray) const
{
    imaging::Color result = colors::black();
    result += RayTracerV2::process_light_ray(scene, properties, hit, ray, light_ray);
    result += compute_specular(scene, properties, hit, ray, light_ray);
    return result;
}

imaging::Color raytracers::_private_::RayTracerV3::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
{
    imaging::Color result = colors::black();
    result += RayTracerV2::determine_color(scene, properties, hit, ray);
    result += process_lights(scene, properties, hit, ray);
    return result;
}


raytracer::RayTracer raytracer::raytracers::v3()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}