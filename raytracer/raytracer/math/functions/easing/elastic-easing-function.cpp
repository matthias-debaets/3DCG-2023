#include "math/functions/easing/elastic-easing-function.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace math::functions;

//\frac{-\cos\left(10x\right)}{x+1}+1

EasingFunction math::functions::easing::elastic(const int a, const int b)
{
    std::function<double(double)> lambda = [a, b](double t) {
        double x = (-cos(a * t) / ((5*t/b) + 1)) + 1;
        assert(interval(0.0, 1.0).contains(x));

        return x;
    };
    
    return from_lambda(lambda);
}