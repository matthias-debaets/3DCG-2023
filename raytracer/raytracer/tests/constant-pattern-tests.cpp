#ifdef TEST_BUILD

#include "Catch.h"
#include "patterns/patterns.h"


TEST_CASE("Given constant pattern is set to true (2 dimensions), randomly chosen points should alyways be true", "[patterns]")
{
	raytracer::patterns::Pattern2D pattern_2d = raytracer::patterns::constant2d(true);

	REQUIRE(pattern_2d({ 0.0, 0.0 }) == true);
	REQUIRE(pattern_2d({ 1.0, 1.0 }) == true);
	REQUIRE(pattern_2d({ -2.5, 3.7 }) == true);
}

TEST_CASE("Given constant pattern is set to false (2 dimensions), randomly chosen points should alyways be false")
{

}

TEST_CASE("Given constant pattern is set to true (3 dimensions), randomly chosen points should alyways be true")
{

}

TEST_CASE("Given constant pattern is set to false (3 dimensions), randomly chosen points should alyways be false")
{

}

#endif