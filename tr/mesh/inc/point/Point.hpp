#pragma once

#include <array>
#include <cmath>

namespace tr
{
    constexpr auto POINTS_2D = 2;
    constexpr auto POINTS_3D = 3;

    template<typename T> struct Point2D
    {
        union
        {
            struct {T u, v;};
            struct {T x, y;};
            T points[POINTS_2D];
        };

        Point2D<T>() : x(0), y(0) {}
        Point2D<T>(T x0, T y0) : x(x0), y(y0) {}
        inline Point2D<T> operator+(const Point2D<T>& point)
        {
            return {this.x + point.x, this.y + point.y};
        }

        inline Point2D<T> operator-(const Point2D<T>& point)
        {
            return {this.x - point.x, this.y - point.y};
        }

        inline Point2D<T> operator*(const float& factor)
        {
            return {this.x*factor, this.y*factor};
        }

        template <typename > friend std::ostream& operator<<(std::ostream& out, const Point2D<T>& p);

    };

    using Point2Di = Point2D<int>;
    using Point2Df = Point2D<float>;

    template <typename T> std::ostream& operator<<(std::ostream& out, const Point2D<T>& p)
    {
        std::string output{"("+std::to_string(p.x) + "," + std::to_string(p.y) + ")\n"};
        out << output;
        return out;
    }


} // namespace tr
