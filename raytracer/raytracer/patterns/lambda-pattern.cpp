#include "patterns/lambda-pattern.h"


namespace raytracer
{
	namespace patterns
	{
		Pattern2D make_pattern(_private_::LambdaPattern2DImplementation::PatternFunctionType function)
		{
			return Pattern2D(std::make_shared<_private_::LambdaPattern2DImplementation>(std::move(function)));
		}

		//Pattern3D make_pattern<_private_::LambdaPattern3DImplementation::PatternFunctionType>(_private_::LambdaPattern3DImplementation::PatternFunctionType function)
		//{
		//	return Pattern3D(std::make_shared<_private_::LambdaPattern3DImplementation>(std::move(function)));
		//}
	}
}
