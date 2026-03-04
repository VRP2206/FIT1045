#include <math.h>
#include "catch_amalgamated.hpp"

using Catch::Approx;

// You need something to test. Here is a simple angle calculator:

/**
 * Calculate the angle between two points in degrees.
 *
 * @param x1 The x-coordinate of the first point.
 * @param y1 The y-coordinate of the first point.
 * @param x2 The x-coordinate of the second point.
 * @param y2 The y-coordinate of the second point.
 * @return double the angle in degrees.
 */
double calculate_angle(double x1, double y1, double x2, double y2)
{
    // should be: double angle = atan2(y2 - y1, x2 - x1) * (180 / M_PI);
    double angle = atan2(y2 - y1, x2 - x1) * (180 / M_PI);
    return angle;
}

// Test cases for the angle calculator

TEST_CASE("Angle Calculation - Basic Test")
{
    double angle = calculate_angle(0, 0, 1, 1);
    REQUIRE(angle == Approx(45.0));
}