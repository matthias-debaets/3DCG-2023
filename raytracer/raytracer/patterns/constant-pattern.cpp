#include "constant-pattern.h"

using namespace math;
using namespace raytracer;

namespace patterns
{
	class ConstantPattern2D : public raytracer::patterns::_private_::Pattern2DImplementation
	{
	private:
		bool constantValue;

	public:
		ConstantPattern2D(bool value) : constantValue(value) {}

		bool at(const math::Point2D& point) const override {
			return constantValue;
		}
	};

	class ConstantPattern3D : public raytracer::patterns::_private_::Pattern3DImplementation
	{
	private:
		bool constantValue;

	public:
		ConstantPattern3D(bool value) : constantValue(value) {}

		bool at(const math::Point3D& point) const override {
			return constantValue;
		}
	};

	Pattern2D constant2d(bool value)
	{
		return Pattern2D(std::make_shared<ConstantPattern2D>(value));
	}

	Pattern3D constant3d(bool value)
	{
		return Pattern3D(std::make_shared<ConstantPattern3D>(value));
	}
}
