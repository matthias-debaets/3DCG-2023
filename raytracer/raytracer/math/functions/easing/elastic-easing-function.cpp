#include "math/functions/easing/elastic-easing-function.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace math::functions;

//\frac{-\cos\left(10x\right)}{x+1}+1

EasingFunction math::functions::easing::elastic()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 2.0).contains(t));

        return t;
    };

    return from_lambda(lambda);
}
