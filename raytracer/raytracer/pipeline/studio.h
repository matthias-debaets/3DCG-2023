#pragma once
#include "pipeline-builder.h"
#include "wif-consumer.h"
#include "wif-processor.h"
#include "base64-processor.h"
#include "text-writer-consumer.h"


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> studio();
    }
}
