#include "Catch.h"
#include "math/transformation2d.h"
#include "math/transformation3d.h"

using namespace math;

#define V(...)     (__VA_ARGS__)
#define P(...)     (__VA_ARGS__)
#define angle(...) (__VA_ARGS__)


#define TEST_TRANSLATION2D(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::translation(Vector2D v);  \
        auto original = Point2D p;                                       \
        auto transformed = Point2D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_ROTATION2D(angle_deg, p, q)                                      \
    TEST_CASE("Rotation by " #angle_deg " degrees of " #p " should yield " #q) \
    {                                                                        \
        auto transformation = transformations::rotate(Angle::degrees(angle_deg)); \
        auto original = Point2D p;                                           \
        auto transformed = Point2D q;                                        \
        auto& m = transformation.transformation_matrix;                      \
        auto& im = transformation.inverse_transformation_matrix;             \
                                                                             \
        CHECK(m * original == approx(transformed));                          \
        CHECK(im * transformed == approx(original));                         \
    }


#define TEST_SCALING2D(sx, sy, p, q)                                     \
    TEST_CASE("Scaling by " #sx ", " #sy " of " #p " should yield " #q)   \
    {                                                                    \
        auto transformation = transformations::scale(sx, sy);            \
        auto original = Point2D p;                                       \
        auto transformed = Point2D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_TRANSLATION3D(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::translation(Vector3D v);    \
        auto original = Point3D p;                                       \
        auto transformed = Point3D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_ROTATION3D_X(angle_deg, p, q)                                   \
    TEST_CASE("Rotation around x-axis by " #angle_deg " degrees of " #p " should yield " #q) \
    {                                                                        \
        auto transformation = transformations::rotate_x(Angle::degrees(angle_deg)); \
        auto original = Point3D p;                                           \
        auto transformed = Point3D q;                                        \
        auto& m = transformation.transformation_matrix;                      \
        auto& im = transformation.inverse_transformation_matrix;             \
                                                                             \
        CHECK(m * original == approx(transformed));                          \
        CHECK(im * transformed == approx(original));                         \
    }

#define TEST_ROTATION3D_Y(angle_deg, p, q)                                   \
    TEST_CASE("Rotation around y-axis by " #angle_deg " degrees of " #p " should yield " #q) \
    {                                                                        \
        auto transformation = transformations::rotate_y(Angle::degrees(angle_deg)); \
        auto original = Point3D p;                                           \
        auto transformed = Point3D q;                                        \
        auto& m = transformation.transformation_matrix;                      \
        auto& im = transformation.inverse_transformation_matrix;             \
                                                                             \
        CHECK(m * original == approx(transformed));                          \
        CHECK(im * transformed == approx(original));                         \
    }

#define TEST_ROTATION3D_Z(angle_deg, p, q)                                   \
    TEST_CASE("Rotation around z-axis by " #angle_deg " degrees of " #p " should yield " #q) \
    {                                                                        \
        auto transformation = transformations::rotate_z(Angle::degrees(angle_deg)); \
        auto original = Point3D p;                                           \
        auto transformed = Point3D q;                                        \
        auto& m = transformation.transformation_matrix;                      \
        auto& im = transformation.inverse_transformation_matrix;             \
                                                                             \
        CHECK(m * original == approx(transformed));                          \
        CHECK(im * transformed == approx(original));                         \
    }

#define TEST_SCALING3D(sx, sy, sz, p, q)                                 \
    TEST_CASE("Scaling by " #sx ", " #sy ", " #sz " of " #p " should yield " #q) \
    {                                                                    \
        auto transformation = transformations::scale(sx, sy, sz);        \
        auto original = Point3D p;                                       \
        auto transformed = Point3D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

TEST_TRANSLATION2D(V(1, 0), P(2, 3), P(3, 3))
TEST_TRANSLATION2D(V(4, 1), P(2, 3), P(6, 4))
TEST_SCALING2D(2, 3, P(1, 2), P(2, 6))
TEST_SCALING2D(0.5, 0.5, P(2, 4), P(1, 2))
TEST_ROTATION2D(90, P(1, 0), P(0, 1))
TEST_ROTATION2D(0, P(1, 2), P(1, 2))

TEST_TRANSLATION3D(V(1, 0, 0), P(2, 3, 4), P(3, 3, 4))
TEST_TRANSLATION3D(V(4, 1, 2), P(2, 3, 4), P(6, 4, 6))
TEST_SCALING3D(2, 3, 4, P(1, 2, 3), P(2, 6, 12))
TEST_SCALING3D(0.5, 0.5, 0.5, P(2, 4, 6), P(1, 2, 3))
TEST_ROTATION3D_X(90, P(1, 0, 0), P(1, 0, 0))
TEST_ROTATION3D_Y(90, P(0, 1, 0), P(0, 1, 0))
TEST_ROTATION3D_Z(180, P(0, 0, 1), P(0, 0, 1))