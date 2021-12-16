#include "primitives/triangle-primitive.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include "math/quadratic_equation.h"
#include "performance/performance.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        TriangleImplementation(const math::Point3D& vertex1, const math::Point3D& vertex2, const math::Point3D& vertex3) : vertex1(vertex1), vertex2(vertex2), vertex3(vertex3)
        {
            norm = ((vertex2 - vertex1).cross(vertex3 - vertex1)).normalized();
        }

        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            hit->t = t;
            hit->position = ray.at(hit->t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
            hit->normal = norm;
        }

    	bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
        {
            auto t = (vertex1 - ray.origin).dot(norm) / ray.direction.dot(norm);
            if (t < 0 || t >= hit->t)
            {
                return false;
            }
            auto H = ray.origin + ray.direction * t;
        	if ((vertex2-vertex1).cross(H-vertex1).dot(norm) >= 0)
        	{
                if ((vertex3 - vertex2).cross(H - vertex2).dot(norm) >= 0)
                {
                    if ((vertex1 - vertex3).cross(H - vertex3).dot(norm) >= 0)
                    {
                        initialize_hit(hit, ray, t);
						return true;
                    }
                }
        	}
            return false;
        	
        }

    	std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> hits;

            auto t = (vertex1 - ray.origin).dot(norm) / ray.direction.dot(norm);
            auto H = ray.origin + ray.direction * t;
        	if ((vertex2-vertex1).cross(H-vertex1).dot(norm) >= 0)
        	{
                if ((vertex3 - vertex2).cross(H - vertex2).dot(norm) >= 0)
                {
                    if ((vertex1 - vertex3).cross(H - vertex3).dot(norm) >= 0)
                    {
                        const auto hit = std::make_shared<Hit>();

                        initialize_hit(hit.get(), ray, t);
                        hits.push_back(hit);
                    }
                }
        	}
            return hits;
        }
    	

		Box bounding_box() const override
		{
			double min_x = std::min(std::min(vertex1.x(), vertex2.x()), vertex3.x());
			double max_x = std::max(std::max(vertex1.x(), vertex2.x()), vertex3.x());
			double min_y = std::min(std::min(vertex1.y(), vertex2.y()), vertex3.y());
			double max_y = std::max(std::max(vertex1.y(), vertex2.y()), vertex3.y());
			double min_z = std::min(std::min(vertex1.z(), vertex2.z()), vertex3.z());
			double max_z = std::max(std::max(vertex1.z(), vertex2.z()), vertex3.z());
			return Box(interval(min_x, max_x), interval(min_y, max_y), interval(min_z, max_z));
		}

    private:
        const Point3D vertex1;
        const Point3D vertex2;
        const Point3D vertex3;
        Vector3D norm;
    };
}

Primitive raytracer::primitives::triangle(const math::Point3D& vertex1, const math::Point3D& vertex2, const math::Point3D& vertex3)
{
    return Primitive(std::make_shared<TriangleImplementation>( vertex1, vertex2,  vertex3));
}
