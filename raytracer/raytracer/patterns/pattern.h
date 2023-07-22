#pragma once

#include "math/point.h"
#include <memory>

namespace raytracer
{
	namespace patterns
	{
		namespace _private_
		{
			class Pattern2DImplementation
			{
			public:
				//Pattern2DImplementation() = default;

				virtual bool at(const math::Point2D& point) const = 0;
			};

			class Pattern3DImplementation
			{
			public:
				//Pattern3DImplementation() = default;

				virtual bool at(const math::Point3D& point) const = 0;
			};
		}

	}

	class Pattern2D
	{
	private:
		std::shared_ptr<patterns::_private_::Pattern2DImplementation> implementation;
	public:
		explicit Pattern2D(std::shared_ptr<patterns::_private_::Pattern2DImplementation> impl = nullptr) : implementation(std::move(impl)) {}

		bool operator()(const math::Point2D& point) const
		{
			return implementation->at(point);
		} 
	};

	class Pattern3D
	{
	private:
		std::shared_ptr<patterns::_private_::Pattern3DImplementation> implementation;
	public:
		explicit Pattern3D(std::shared_ptr<patterns::_private_::Pattern3DImplementation> impl = nullptr) : implementation(std::move(impl)) {}

		bool operator()(const math::Point3D& point) const
		{
			return implementation->at(point);
		}
	};
}
