#include "patterns/lambda-pattern.h"

using namespace raytracer;
using namespace patterns;

namespace my_namespace
{
	Pattern2D make_pattern(_private_::LambdaPattern2DImplementation::PatternFunctionType function)
	{
		return Pattern2D(std::make_shared<_private_::LambdaPattern2DImplementation>(function));
	}

	Pattern3D make_pattern(_private_::LambdaPattern3DImplementation::PatternFunctionType function)
	{
		return Pattern3D(std::make_shared<_private_::LambdaPattern3DImplementation>(function));
	}
}
