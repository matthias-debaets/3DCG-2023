#ifdef TEST_BUILD

#include "samplers/samplers.h"
#include "Catch.h"

bool inMiddleRectangle(math::Point2D point, math::Rectangle2D rectangle)
{
	if (point.x() >= rectangle.origin.x() && point.x() <= (rectangle.origin + rectangle.x_axis).x() && point.y() >= rectangle.origin.y() && point.y() <= (rectangle.origin + rectangle.y_axis).y())
	{
		return true;
	}
	return false;
}

bool check_half_jittered(const std::vector<math::Point2D> points, const std::vector<math::Rectangle2D> rectangles)
{
	bool compare = true;
	std::vector<math::Rectangle2D> check;
	for (unsigned i = 0; i < rectangles.size() && compare; i++)
	{
		for (unsigned k = 0; k < points.size(); k++)
		{
			if (inMiddleRectangle(points[k], rectangles[i]))
			{
				if (std::find(check.begin(), check.end(), rectangles[i]) != check.end()) {
					compare = false;
					break;
				}
				else
				{
					check.push_back(rectangles[i]);
					compare = true;
					break;
				}
			}
			compare = false;
		}
	}
	return compare;
}

TEST_CASE("Given a rectangle[0, 1]×[0, 1] and 1×1 samples, the returned sample should be between [0.25,0.75]×[0.25,0.75]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(1, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles = { math::Rectangle2D(math::Point2D(0.25, 0.25), math::Vector2D(0.5, 0), math::Vector2D(0, 0.5)) };
	bool compare = check_half_jittered(points, rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle[0, 2]×[0, 1] and 1×1 samples, the returned sample should be between [0.5,1.5]×[0.25,0.75]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 1));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(1, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles = { math::Rectangle2D(math::Point2D(0.5, 0.25), math::Vector2D(1, 0), math::Vector2D(0, 0.5)) };
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

TEST_CASE("Given a rectangle[0, 1]×[0, 2] and 1×1 samples, the returned sample should be between [0.25,0.75]×[0.5,1.5]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 2));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(1, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles = { math::Rectangle2D(math::Point2D(0.25, 0.5), math::Vector2D(0.5, 0), math::Vector2D(0, 1)) };
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [5,9]×[2,6] and 1×1 samples, the returned sample should inside [6,8]×[3,5]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(5, 2), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(1, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles = { math::Rectangle2D(math::Point2D(6, 3), math::Vector2D(2, 0), math::Vector2D(0, 2)) };
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,8]×[0,8] and 2×2 samples, the returned samples should inside [1,3]×[1,3], [1,3]×[5,7], [5,7]×[1,3] and [5,7]×[5,7]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(8, 0), math::Vector2D(0, 8));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(2, 2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rectangles.push_back(math::Rectangle2D(math::Point2D(1 + 4*i, 1 + 4*j), math::Vector2D(2, 0), math::Vector2D(0, 2)));
		}
	}
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,8]×[0,8] and 4×4 samples, the returned samples should inside { [0.5+2i,2i+1.5]×[0.5+2j,2j+1.5]|i=0…3,j=0…3}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(8, 0), math::Vector2D(0, 8));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(4, 4);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rectangles.push_back(math::Rectangle2D(math::Point2D(0.5 + 2 * i, 0.5 + 2 * j), math::Vector2D(1, 0), math::Vector2D(0, 1)));
		}
	}
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,6]×[0,4] and 3×2 samples, the returned samples should inside { [0.5+2i,2i+1.5]×[0.5+2j,2j+1.5]|i=0…2,j=0…1}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(6, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(3, 2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rectangles.push_back(math::Rectangle2D(math::Point2D(0.5 + 2 * i, 0.5 + 2 * j), math::Vector2D(1, 0), math::Vector2D(0, 1)));
		}
	}
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,6]×[0,4] and 1×2 samples, the returned samples should inside { [1.5, 4.5]×[0.5+2j,2j+1.5]|i=0,j=0…1}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(6, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(1, 2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles;
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rectangles.push_back(math::Rectangle2D(math::Point2D(1.5, 0.5 + 2 * j), math::Vector2D(3, 0), math::Vector2D(0, 1)));
		}
	}
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,6]×[0,4] and 2×1 samples, the returned samples should inside { [0.75 + 3i, 2.25 + 3i]×[1,3]|i=0...1,j=0…0}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(6, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(2, 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			rectangles.push_back(math::Rectangle2D(math::Point2D(0.75 + 3*i, 1), math::Vector2D(1.5, 0), math::Vector2D(0, 2)));
		}
	}
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,6]×[0,4] and 2×2 samples, the returned samples should inside { [0.75 + 3i, 2.25 + 3i]×[0.5 + 2j,1.5 + 2j]|i=0...1,j=0…1}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(6, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::stratified_half_jittered(2, 2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> rectangles;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rectangles.push_back(math::Rectangle2D(math::Point2D(0.75 + 3 * i, 0.5 + 2*j), math::Vector2D(1.5, 0), math::Vector2D(0, 2)));
		}
	}
	bool compare = check_half_jittered(points, rectangles);

	REQUIRE(compare);

}

#endif