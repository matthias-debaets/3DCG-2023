#include "samplers/n-rooks-sampler.h"

#include <random>

#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
{
    class NRooksSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    private:
        unsigned n;
    public:
        NRooksSampler(unsigned n) : n(n)
        {

        }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            std::vector<int> row;
            std::vector<int> column;

            std::random_device rd;
            std::mt19937 g(rd());
            for (unsigned i = 0; i < n; ++i) 
            {
                row.push_back(i);
                column.push_back(i);
            }
            std::shuffle(row.begin(), row.end(), g);
            std::shuffle(column.begin(), column.end(), g);
        	
            auto rectangles = math::Rasterizer(rectangle, n, n);
            for (unsigned i = 0; i < n; i++)
            {
                double x = (double)rand() / (double)RAND_MAX;
                double y = (double)rand() / (double)RAND_MAX;
                function(rectangles[Position2D(row[i], column[i])].from_relative(Point2D(x, y)));
            }
        }
    };
}

Sampler raytracer::samplers::nrooks(unsigned n)
{
    return Sampler(std::make_shared<NRooksSampler>(n));
}