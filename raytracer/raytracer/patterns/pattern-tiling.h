#pragma once

#include "pattern.h"

 namespace raytracer
 {
	namespace patterns
	{
		Pattern2D tiling(Pattern2D pattern, double width, double height);

		Pattern3D tiling(Pattern3D pattern, double x_size, double y_size, double z_size);

		Pattern2D tiling_x(Pattern2D pattern, double width);

		Pattern2D tiling_y(Pattern2D pattern, double height);
	}
 }