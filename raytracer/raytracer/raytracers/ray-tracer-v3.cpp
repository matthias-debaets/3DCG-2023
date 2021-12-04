#include "ray-tracer-v3.h"

using namespace imaging;
using namespace math;
using namespace raytracer;



imaging::Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const
{
    const Vector3D n_vector = hit.normal;
	Point3D L = light_ray.ray.origin;
    Point3D P = hit.position;
    Point3D E = ray.origin;
    Color CL = light_ray.color;
    Color CP = properties.specular;
    double e = properties.specular_exponent;

    Vector3D i = (P - L).normalized();
    Vector3D r = i.reflect_by(n_vector);
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




raytracer::RayTracer raytracer::raytracers::v3()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}