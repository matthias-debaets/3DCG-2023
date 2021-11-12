#include "samplers/stratified-sampler.h"

#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
{
    class StratifiedSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    private:
        unsigned rows;
        unsigned columns;
    public:
        StratifiedSampler(unsigned rows, unsigned columns) : rows(rows), columns(columns)
        {

        }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            auto rectangles = math::Rasterizer(rectangle, rows, columns);
            for (unsigned i = 0; i < rows; i++)
            {
				for (unsigned j = 0; j < columns; j++)
				{
                    function(rectangles[Position2D(i, j)].center());
				}
            }
        }
    };
}

Sampler raytracer::samplers::stratified_fixed(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<StratifiedSampler>(rows, columns));
}