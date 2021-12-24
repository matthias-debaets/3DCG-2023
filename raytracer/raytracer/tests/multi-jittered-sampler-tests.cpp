#ifdef TEST_BUILD

#include "samplers/samplers.h"
#include "Catch.h"

bool inMJRectangle(math::Point2D point, math::Rectangle2D rectangle)
{
	if (point.x() >= rectangle.origin.x() && point.x() <= (rectangle.origin + rectangle.x_axis).x() && point.y() >= rectangle.origin.y() && point.y() <= (rectangle.origin + rectangle.y_axis).y())
	{
		return true;
	}
	return false;
}

bool check_multi_jittered(const std::vector<math::Point2D> points, const std::vector<math::Rectangle2D> x_rectangles, const std::vector<math::Rectangle2D> y_rectangles)
{
	bool compare = true;
	std::vector<math::Rectangle2D> x_check;
	std::vector<math::Rectangle2D> y_check;
	for (unsigned i = 0; i < points.size() && compare; i++)
	{
		for (unsigned j = 0; j < x_rectangles.size(); j++)
		{
			if (inMJRectangle(points[i], x_rectangles[j]))
			{
				if (std::find(x_check.begin(), x_check.end(), x_rectangles[j]) != x_check.end()) {
					return false;
				}
				else
				{
					x_check.push_back(x_rectangles[j]);
					compare = true;
					break;
				}
			}
			compare = false;
		}
		for (unsigned j = 0; j < y_rectangles.size(); j++)
		{
			if (inMJRectangle(points[i], y_rectangles[j]))
			{
				if (std::find(y_check.begin(), y_check.end(), y_rectangles[j]) != y_check.end()) {
					return false;
				}
				else
				{
					y_check.push_back(y_rectangles[j]);
					compare = true;
					break;
				}
			}
			compare = false;
		}
	}
	return x_check.size() == x_rectangles.size() && y_check.size() == y_rectangles.size();
}

TEST_CASE("Given a rectangle [0,1]×[0,1] and 1 sample, the returnedooc sample should inside [0,1]×[0,1]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1));
	raytracer::Sampler sampler = raytracer::samplers::multijittered(1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles = { math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1)) };
	std::vector<math::Rectangle2D> y_rectangles = { math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1)) };
	bool compare = check_multi_jittered(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [4,8]×[6,7] and 1 sample, the returned sample should inside [4,8]×[6,7]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(4, 6), math::Vector2D(4, 0), math::Vector2D(0, 1));
	raytracer::Sampler sampler = raytracer::samplers::multijittered(1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles = { math::Rectangle2D(math::Point2D(4, 6), math::Vector2D(4, 0), math::Vector2D(0, 1)) };
	std::vector<math::Rectangle2D> y_rectangles = { math::Rectangle2D(math::Point2D(4, 6), math::Vector2D(4, 0), math::Vector2D(0, 1)) };
	bool compare = check_multi_jittered(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,2]×[0,2] and 2×2 samples, 4 samples should be returned. Two samples should have their x - coordinate in[0, 1]. Two samples should have their x - coordinate in[1, 2]. Two samples should have their y - coordinate in[0, 1]. Two samples should have their y - coordinate in[1, 2]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 2));
	raytracer::Sampler sampler = raytracer::samplers::multijittered(2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles;
	std::vector<math::Rectangle2D> y_rectangles;
	for (unsigned i = 0; i < 4; i++)
	{
		x_rectangles.push_back(math::Rectangle2D(math::Point2D(0.5*i, 0), math::Vector2D(0.5, 0), math::Vector2D(0, 2)));
		y_rectangles.push_back(math::Rectangle2D(math::Point2D(0, 0.5*i), math::Vector2D(2, 0), math::Vector2D(0, 0.5)));
	}

	bool compare = check_multi_jittered(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [1,10]×[1,10] and 3×3 samples, 9 samples should be returned. 1 point should have its x_coord in { [1+i, 2+i] X [1, 10] | i=0...8}. 1 point should have its y_coord in { [1, 10] X [1 + i, 2 + i] | i=0...8}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(1, 1), math::Vector2D(9, 0), math::Vector2D(0, 9));
	raytracer::Sampler sampler = raytracer::samplers::multijittered(3);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles;
	std::vector<math::Rectangle2D> y_rectangles;
	for (unsigned i = 0; i < 9; i++)
	{
		x_rectangles.push_back(math::Rectangle2D(math::Point2D(1 + i, 1), math::Vector2D(1, 0), math::Vector2D(0, 9)));
		y_rectangles.push_back(math::Rectangle2D(math::Point2D(1, 1 + i), math::Vector2D(9, 0), math::Vector2D(0, 1)));
	}

	bool compare = check_multi_jittered(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,16]×[0,8] and 4×4 samples, 16 samples should be returned. 1 point should have its x_coord in { [i, 1+i] X [0, 8] | i=0...15}. 1 point should have its y_coord in { [0, 16] X [0.5 * i, 0.5 + 0.5 * i] | i=0...15}")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(16, 0), math::Vector2D(0, 8));
	raytracer::Sampler sampler = raytracer::samplers::multijittered(4);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles;
	std::vector<math::Rectangle2D> y_rectangles;
	for (unsigned i = 0; i < 16; i++)
	{
		x_rectangles.push_back(math::Rectangle2D(math::Point2D(i, 0), math::Vector2D(1, 0), math::Vector2D(0, 8)));
		y_rectangles.push_back(math::Rectangle2D(math::Point2D(0, 0.5 * i), math::Vector2D(16, 0), math::Vector2D(0, 0.5)));
	}

	bool compare = check_multi_jittered(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

#endif