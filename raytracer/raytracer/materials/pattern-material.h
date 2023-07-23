#pragma once

#include "materials/material.h"
#include "patterns/pattern.h"

namespace raytracer
{
    namespace materials
    {
        Material pattern2d(const raytracer::Pattern2D& pattern, const Material& m1, const Material& m2);
        Material pattern3d(const raytracer::Pattern3D& pattern, const Material& m1, const Material& m2);
    }
}
