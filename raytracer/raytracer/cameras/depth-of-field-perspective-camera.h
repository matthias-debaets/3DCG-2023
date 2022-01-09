#pragma once

#include "cameras/displaceable-camera.h"
#include "math/point.h"
#include <memory>
#include "samplers/samplers.h"


namespace raytracer
{
    namespace cameras
    {
        namespace _private_
        {
            class DepthOfFieldPerspectiveCamera : public DisplaceableCamera
            {
            public:
                DepthOfFieldPerspectiveCamera(const math::Matrix4x4 transformation, const std::vector<Camera>&);

            protected:
                void enumerate_untransformed_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const;

            private:
                std::vector<Camera> cameras;
            };
        }

        /// <summary>
        /// Creates a depth_of_field_perspective camera.
        /// </summary>
        /// <param name="eye">The camera's location</param>
        /// <param name="look_at">The point the camera is directed at</param>
        /// <param name="up">Specifies how the camera is tilted sideways. (0,1,0) is standard.</param>
        /// <param name="distance">Distance between eye and view plane.</param>
        Camera depth_of_field_perspective(
            const math::Point3D& eye,
            const math::Point3D& look_at,
            const math::Vector3D& up,
            double distance,
            double aspect_ratio,
            double eye_size,
            Sampler eye_sampler);
    }
}