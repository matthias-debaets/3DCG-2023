#include "primitives/bbacc.h"

using namespace raytracer;

namespace
{
	class BoundingBoxAccelerator : public raytracer::primitives::_private_::PrimitiveImplementation
	{
		raytracer::Primitive primitive;
		math::Box box;

	public:
		BoundingBoxAccelerator(Primitive primitive) : primitive(primitive), box(primitive->bounding_box()) {	}

		bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
		{
			if (box.is_hit_positively_by(ray))
			{
				return primitive->find_first_positive_hit(ray, hit);
			}
			return false;
		}
		
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			if (box.is_hit_positively_by(ray))
			{
				return primitive->find_all_hits(ray);
			}
			return hits;
		}

		math::Box bounding_box() const override
		{
			return box;
		}
	};
}

Primitive primitives::bounding_box_accelerator(Primitive primitive)
{
	return Primitive(std::make_shared<BoundingBoxAccelerator>(primitive));
}