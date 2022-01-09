#include "depth-of-field-perspective-camera.h"
#include "math/vector.h"
#include <assert.h>

#include "easylogging++.h"
#include "perspective-camera.h"


using namespace raytracer;
using namespace raytracer::cameras;
using namespace math;

raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::DepthOfFieldPerspectiveCamera(const math::Matrix4x4 transformation, const std::vector<Camera>& cameras)
    : DisplaceableCamera(transformation), cameras(cameras)
{
    // NOP
}

void raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::enumerate_untransformed_rays(const math::Point2D& point, std::function<void(const math::Ray&)> callback) const
{
    assert(interval(0.0, 1.0).contains(point.x()));
    assert(interval(0.0, 1.0).contains(point.y()));

    for (auto &camera : cameras)
    {
        camera->enumerate_rays(point, callback);
    }
}

Camera raytracer::cameras::depth_of_field_perspective(
    const math::Point3D& eye,
    const math::Point3D& look_at,
    const math::Vector3D& up,
    double distance,
    double aspect_ratio,
    double eye_size,
    Sampler eye_sampler)
{
    assert(up.is_unit());

    Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);
    std::vector<Camera> cameras;
    auto canonical_up = Vector3D(0, 1, 0);

    const auto canonical_look_at = math::Point3D(0, 0, math::distance(eye, look_at));
    assert(canonical_look_at.x() == 0);
    assert(canonical_look_at.y() == 0);
    assert(canonical_look_at.z() == math::distance(eye, look_at));

    const auto eye_area = math::Rectangle2D(Point2D(eye.x() - (eye_size / 2), eye.y() - (eye_size / 2)), Vector2D(eye_size, 0), Vector2D(0, eye_size));

    assert(eye_area.x_axis.x() == eye_size && eye_area.y_axis.y() == eye_size);
    assert(eye_area.center() == Point2D(0, 0));

    const std::function<void(const Point2D&)> add_camera = [canonical_up, canonical_look_at, distance, aspect_ratio, &cameras](const Point2D& p)
    {
        const auto canonical_eye = Point3D(p.x(), p.y(), 0);
        const auto camera = raytracer::cameras::perspective(canonical_eye, canonical_look_at, canonical_up, distance, aspect_ratio);
    	cameras.push_back(camera);
    };
    eye_sampler->sample(eye_area, add_camera);
	
    return Camera(std::make_shared<_private_::DepthOfFieldPerspectiveCamera>(transformation, cameras));
}