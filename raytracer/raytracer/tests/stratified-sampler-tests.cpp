#ifdef TEST_BUILD

#include "samplers/stratified-sampler.h"
#include "Catch.h"

TEST_CASE("Given a rectangle[0, 1]×[0, 1] and 1×1 samples, the returned sample should be{ (0.5,0.5) }")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(1, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct = { math::Point2D(0.5, 0.5) };

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
TEST_CASE("Given a rectangle [5,7]×[3,7] and 1×1 samples, the returned sample should be {(6,5)}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(5, 3), math::Vector2D(2, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(1, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct = { math::Point2D(6, 5) };

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
TEST_CASE("Given a rectangle [0,2]×[0,2] and 1×1 samples, the returned sample should be {(1,1)}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 2));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(1, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct = { math::Point2D(1, 1) };

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
TEST_CASE("Given a rectangle [0,4]×[0,2] and 2×1 samples, the returned samples should be  {(1,1),(3,1)}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 2));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(2, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct = { math::Point2D(1, 1), math::Point2D(3,1) };

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
TEST_CASE("Given a rectangle [0,2]×[0,4] and 1×2 samples, the returned samples should be {(1,1),(1,3)}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(1, 2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct = { math::Point2D(1,1), math::Point2D(1, 3) };

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
TEST_CASE("Given a rectangle [0,4]×[0,4] and 4×4 samples, the returned samples should be {(i+0.5,j+0.5)|i=0…3,j=0…3}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(4, 4);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			correct.push_back(math::Point2D(0.5 + i, 0.5 + j));
		}
	}

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
TEST_CASE("Given a rectangle [0,2]×[0,2] and 1×4 samples, the returned samples should be {(1,j*0.5+0.25)|j=0…3}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 2));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(1, 4);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct;
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			correct.push_back(math::Point2D(1, 0.25 + j*0.5));
		}
	}

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
TEST_CASE("Given a rectangle [0,4]×[0,2] and 4×2 samples, the returned samples should be {(0.5+i,j+0.5)|i=0...4 & j=0…2}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 2));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(4, 2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			correct.push_back(math::Point2D(0.5+i, j + 0.5));
		}
	}

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);
}
TEST_CASE("Given a rectangle [1,7]×[0,2] and 3×2 samples, the returned samples should be {(2+2i,j+0.5)|i=0...3 & j=0…2}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(1, 0), math::Vector2D(6, 0), math::Vector2D(0, 2));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(3, 2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			correct.push_back(math::Point2D(2+2*i, j + 0.5));
		}
	}

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
TEST_CASE("Given a rectangle [1,2]×[1,2] and 2×2 samples, the returned samples should be {(0.25+0.5i,0.5j+0.25)|i=0...2 & j=0…2}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(1, 1), math::Vector2D(1, 0), math::Vector2D(0, 1));
	raytracer::Sampler sampler = raytracer::samplers::stratified_fixed(2, 2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Point2D> correct;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			correct.push_back(math::Point2D(1.25 + 0.5 * i, j*0.5 + 1.25));
		}
	}

	bool compare = true;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < correct.size(); j++) {
			if (points[i] == correct[j]) {
				compare = true;
				break;
			}
			compare = false;
		}
	}
	REQUIRE(compare);

}
#endif