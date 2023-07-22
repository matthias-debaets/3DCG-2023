#include "constant-pattern.h"

using namespace math;
using namespace raytracer;

namespace
{
	class ConstantPattern2D : public raytracer::patterns::Pattern2DImplementation
	{
	private:
		bool constantValue;

	public:
		ConstantPattern2D(bool value) : constantValue(value) {}

		bool at(const math::Point2D& point) const override {
			return constantValue;
		}
	};

	class ConstantPattern3D : public raytracer::patterns::Pattern3DImplementation
	{
	private:
		bool constantValue;

	public:
		ConstantPattern3D(bool value) : constantValue(value) {}

		bool at(const math::Point3D& point) const override {
			return constantValue;
		}
	};

	patterns::Pattern2D constant2d(bool value)
	{
		return patterns::Pattern2D(std::make_shared<ConstantPattern2D>(value));
	}

	patterns::Pattern3D constant3d(bool value)
	{
		return patterns::Pattern3D(std::make_shared<ConstantPattern3D>(value));
	}
}
