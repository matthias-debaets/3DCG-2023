#pragma once

#include "pattern.h"

namespace raytracer
{
	namespace patterns
	{
		namespace _private_
		{
			class LambdaPattern2DImplementation : public raytracer::patterns::_private_::Pattern2DImplementation
			{

			public:
				using PatternFunctionType = bool (*)(const math::Point2D&);

				explicit LambdaPattern2DImplementation(PatternFunctionType function) : m_function(function) {}

				bool at(const math::Point2D& point) const override
				{
					return m_function(point);
				}

			private:
				PatternFunctionType m_function;
			};

			class LambdaPattern3DImplementation : public raytracer::patterns::_private_::Pattern3DImplementation
			{
			public:
				using PatternFunctionType = bool (*)(const math::Point3D&);

				explicit LambdaPattern3DImplementation(PatternFunctionType function) : m_function(function) {}

				bool at(const math::Point3D& point) const override
				{
					return m_function(point);
				}
			private:
				PatternFunctionType m_function;
			};
		}

		Pattern2D make_pattern(_private_::LambdaPattern2DImplementation::PatternFunctionType function);

		Pattern3D make_pattern(_private_::LambdaPattern3DImplementation::PatternFunctionType function);
	}
}