#include "patterns/constant-pattern.h"

using namespace math;
using namespace raytracer;

namespace
{
	class ConstantPattern2D : public raytracer::patterns::_private_::Pattern2DImplementation
	{
	public:
		ConstantPattern2D(bool value) : constantValue(value) {}

		bool at(const math::Point2D& point) const override {
			return constantValue;
		}

	private:
		bool constantValue;
	};

	class ConstantPattern3D : public raytracer::patterns::_private_::Pattern3DImplementation
	{
	public:
		ConstantPattern3D(bool value) : constantValue(value) {}

		bool at(const math::Point3D& point) const override {
			return constantValue;
		}

	private:
		bool constantValue;
	};
}

Pattern2D patterns::constant2d(bool value)
{
	return Pattern2D(std::make_shared<ConstantPattern2D>(value));
}

Pattern3D patterns::constant3d(bool value)
{
	return Pattern3D(std::make_shared<ConstantPattern3D>(value));
}

