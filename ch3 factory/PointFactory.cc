/*
 * description:
 * author@elecfrog
 */
#pragma once


#include <cmath>
#include <ostream>

namespace Geometry
{
    struct Point {

        Point(float x, float y) : x(x), y(y) {}

        float x, y;

        friend std::ostream &operator<<(std::ostream &os, const Point &point) {
            os << "x: " << point.x << " y: " << point.y;
            return os;
        }
    };


    namespace PointFactory {
        static Point PointFromVector3(float x, float y) {
            return Point{x, y};
        };

        static Point PointFromPolar(float rho, float theta) {
            return Point{rho * std::cos(theta), rho * std::sin(theta)};
        };
    }
}

int main()
{
    Geometry::Point p{0.f, 0.f};
    auto pfv = Geometry::PointFactory::PointFromVector3(0.f, 0.f);
    auto pfp = Geometry::PointFactory::PointFromPolar(0.f, 0.f);
}

