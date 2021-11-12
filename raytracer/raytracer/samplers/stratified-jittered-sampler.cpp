#include "samplers/stratified-jittered-sampler.h"

#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
{
    class stratifiedJitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    private:
        unsigned rows;
        unsigned columns;
    public:
        stratifiedJitteredSampler(unsigned rows, unsigned columns) : rows(rows), columns(columns)
        {

        }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            auto rectangles = math::Rasterizer(rectangle, rows, columns);
            for (unsigned i = 0; i < rows; i++)
            {
                for (unsigned j = 0; j < columns; j++)
                {
                    double x = (double)rand() / (double)RAND_MAX;
                    double y = (double)rand() / (double)RAND_MAX;
                    function(rectangles[Position2D(i, j)].from_relative(Point2D(x, y)));
                }
            }
        }
    };
}

Sampler raytracer::samplers::stratified_jittered(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<stratifiedJitteredSampler>(rows, columns));
}