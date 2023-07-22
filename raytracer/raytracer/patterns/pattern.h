#pragma once
#include "math/point.h"

namespace raytracer
{
	namespace patterns
	{
		class Pattern2DImplementation
		{
		public:
			Pattern2DImplementation() = default;

			virtual bool at(const math::Point2D& point) const;
		};

		class Pattern3DImplementation
		{
		public:
			Pattern3DImplementation() = default;

			virtual bool at(const math::Point3D& point) const;
		};

		class Pattern2D
		{
		private:
			std::shared_ptr<patterns::Pattern2DImplementation> implementation;
		public:
			explicit Pattern2D(std::shared_ptr<patterns::Pattern2DImplementation> impl) : implementation(std::move(impl)) {}

			bool operator()(const math::Point2D& point) const
			{
				return implementation->at(point);
			}
		};

		class Pattern3D
		{
		private:
			std::shared_ptr<patterns::Pattern3DImplementation> implementation;
		public:
			explicit Pattern3D(std::shared_ptr<patterns::Pattern3DImplementation> impl) : implementation(std::move(impl)) {}

			bool operator()(const math::Point3D& point) const
			{
				return implementation->at(point);
			}
		};
	}
}
