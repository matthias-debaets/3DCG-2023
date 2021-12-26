#pragma once

#include "primitives/primitive.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        Primitive mesh(const std::string& path);
    }
}