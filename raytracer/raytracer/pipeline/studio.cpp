#include "studio.h"

using namespace raytracer::pipeline;


namespace
{
    class Studio : public Consumer<std::shared_ptr<imaging::Bitmap>>
    {
    public:
        Studio()
        {
            // NOP
        }

        void consume(std::shared_ptr<imaging::Bitmap> frame) override
        {
            auto pipeline_builder = raytracer::pipeline::_private_::PipelineBuilderStart<std::shared_ptr<imaging::Bitmap>>(frame);
            auto temp = raytracer::pipeline::start(frame);
            auto wif_temp = wif();
            auto base64_temp = base64();
            auto text_writer_temp = text_writer(std::cout);
            auto exec_wif = pipeline_builder >> wif_temp;
            auto exec_base64 = exec_wif >> base64_temp;
        	exec_base64 >> text_writer_temp;
        		
        }
    };
}


std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::studio()
{
    return std::make_shared<Studio>();
}
