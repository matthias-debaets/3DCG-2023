#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>

#include "ray-tracer-v1.h"


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV2 : public RayTracerV1
            {
            public:
                TraceResult trace(const Scene& scene, const math::Ray& eye_ray) const override;
                virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const override;
            protected:
                virtual imaging::Color process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const;
                virtual imaging::Color process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightSource light_source) const;
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const;
                virtual imaging::Color compute_diffuse(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v2();
    }
}
