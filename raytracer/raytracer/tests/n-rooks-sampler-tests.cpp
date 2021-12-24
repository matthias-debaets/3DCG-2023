#ifdef TEST_BUILD

#include "samplers/samplers.h"
#include "Catch.h"

bool inNrooksRectangle(math::Point2D point, math::Rectangle2D rectangle)
{
	if (point.x() >= rectangle.origin.x() && point.x() <= (rectangle.origin + rectangle.x_axis).x() && point.y() >= rectangle.origin.y() && point.y() <= (rectangle.origin + rectangle.y_axis).y())
	{
		return true;
	}
	return false;
}

bool check_nrooks(const std::vector<math::Point2D> points, const std::vector<math::Rectangle2D> x_rectangles, const std::vector<math::Rectangle2D> y_rectangles)
{
	bool compare = true;
	std::vector<math::Rectangle2D> x_check;
	std::vector<math::Rectangle2D> y_check;
	for (unsigned i = 0; i <  points.size() && compare; i++)
	{
		for (unsigned j = 0; j< x_rectangles.size(); j++)
		{
			if (inNrooksRectangle(points[i], x_rectangles[j]))
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
			if (inNrooksRectangle(points[i], y_rectangles[j]))
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

TEST_CASE("Given a rectangle [0,1]×[0,1] and N=1 sample, the returnedooc sample should inside [0,1]×[0,1]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1));
	raytracer::Sampler sampler = raytracer::samplers::nrooks( 1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles = { math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1)) };
	std::vector<math::Rectangle2D> y_rectangles = { math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1)) };
	bool compare = check_nrooks(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [4,8]×[6,7] and N=1 sample, the returned sample should inside [4,8]×[6,7]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(4, 6), math::Vector2D(4, 0), math::Vector2D(0, 1));
	raytracer::Sampler sampler = raytracer::samplers::nrooks(1);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles = { math::Rectangle2D(math::Point2D(4, 6), math::Vector2D(4, 0), math::Vector2D(0, 1)) };
	std::vector<math::Rectangle2D> y_rectangles = { math::Rectangle2D(math::Point2D(4, 6), math::Vector2D(4, 0), math::Vector2D(0, 1)) };
	bool compare = check_nrooks(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,4]×[0,4] and N=4 samples, 4 samples should be returned.One sample should have its x-coordinate in [0,1].One sample should have its x-coordinate in [1,2].One sample should have its x-coordinate in [2,3].One sample should have its x-coordinate in [3,4].One sample should have its y-coordinate in [0,1].One sample should have its y-coordinate in [1,2].One sample should have its y-coordinate in [2,3].One sample should have its y-coordinate in  [3,4]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::nrooks(4);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles;
	std::vector<math::Rectangle2D> y_rectangles;

	for (unsigned i = 0; i < 4; i ++)
	{
		x_rectangles.push_back(math::Rectangle2D(math::Point2D(i, 0), math::Vector2D(1, 0), math::Vector2D(0, 4)));
		y_rectangles.push_back(math::Rectangle2D(math::Point2D(0, i), math::Vector2D(4, 0), math::Vector2D(0, 1)));
	}
	bool compare = check_nrooks(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,4]×[0,4] and N= 2samples, 2 samples should be returned.One sample should have its x-coordinate in [0,2].One sample should have its x-coordinate in [2,4].One sample should have its y-coordinate in [0,2].One sample should have its y-coordinate in [2,4]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler sampler = raytracer::samplers::nrooks(2);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles;
	std::vector<math::Rectangle2D> y_rectangles;

	for (unsigned i = 0; i < 2; i ++)
	{
		x_rectangles.push_back(math::Rectangle2D(math::Point2D(i*2, 0), math::Vector2D(2, 0), math::Vector2D(0, 4)));
		y_rectangles.push_back(math::Rectangle2D(math::Point2D(0, i*2), math::Vector2D(4, 0), math::Vector2D(0, 2)));
	}
	bool compare = check_nrooks(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}

TEST_CASE("Given a rectangle [0,6]×[0,6] and N= 3 samples, 3 samples should be returned.One sample should have its x-coordinate in [0,2].One sample should have its x-coordinate in [2,4].One sample should have its x-coordinate in [4,6].One sample should have its y-coordinate in [0,2].One sample should have its y-coordinate in [2,4].One sample should have its y-coordinate in [4,6]")
{
	auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(6, 0), math::Vector2D(0, 6));
	raytracer::Sampler sampler = raytracer::samplers::nrooks(3);
	auto points = sampler->sample(rectangle);
	std::vector<math::Rectangle2D> x_rectangles;
	std::vector<math::Rectangle2D> y_rectangles;

	for (unsigned i = 0; i < 3; i++)
	{
		x_rectangles.push_back(math::Rectangle2D(math::Point2D(i * 2, 0), math::Vector2D(2, 0), math::Vector2D(0, 6)));
		y_rectangles.push_back(math::Rectangle2D(math::Point2D(0, i * 2), math::Vector2D(6, 0), math::Vector2D(0, 2)));
	}
	bool compare = check_nrooks(points, x_rectangles, y_rectangles);
	REQUIRE(compare);

}


#endif