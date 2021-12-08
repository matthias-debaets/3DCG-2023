#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>

#include "ray-tracer-v4.h"


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV5 : public RayTracerV4
            {
            public:
            protected:
                imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay& light_ray) const override;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v5();
    }
}
