#pragma once

#include "imaging/bitmap.h"
#include "pipeline/processor.h"


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<imaging::Bitmap>>> motion_blur(unsigned, unsigned);
    }
}