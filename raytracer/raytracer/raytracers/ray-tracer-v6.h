#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>

#include "ray-tracer-v5.h"


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV6 : public RayTracerV5
            {
            public:
                TraceResult trace(const Scene& scene, const math::Ray& eye_ray) const override;
            protected:
                imaging::Color determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, double weight) const;
                TraceResult trace(const Scene& scene, const math::Ray& eye_ray, const double weight) const;
                imaging::Color compute_reflection(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit,const math::Ray& eye_ray, double weight) const;

            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v6();
    }
}