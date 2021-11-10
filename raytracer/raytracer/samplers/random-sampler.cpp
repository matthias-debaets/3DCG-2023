#include "samplers/random-sampler.h"
#include "random"

using namespace math;
using namespace raytracer;


namespace
{
    class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    private:
        const int n;
    public:
        RandomSampler(const int n): n(n)
        {

        }
    	
        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
        	for (int i = 0; i <= n; i++)
        	{
                double x = (double)rand() / (double)RAND_MAX;
                double y = (double)rand() / (double)RAND_MAX;
                function(rectangle.from_relative(Point2D(x, y)));
        	}
        }
    };
}

Sampler raytracer::samplers::random(const int n)
{
    return Sampler(std::make_shared<RandomSampler>(n));
}