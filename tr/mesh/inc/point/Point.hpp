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
        inline Point2D<T> operator+(const Point2D<T>& point) const
        {
            return {this.x + point.x, this.y + point.y};
        }

        inline Point2D<T> operator-(const Point2D<T>& point) const
        {
            return {this.x - point.x, this.y - point.y};
        }

        inline Point2D<T> operator*(const float& factor) const
        {
            return {this.x*factor, this.y*factor};
        }

        template <typename > friend std::ostream& operator<<(std::ostream& out, const Point2D<T>& p);

    };

     template<typename T> struct Point3D
    {
        union
        {
            struct {T ivert, iuv, inorm;};
            struct {T x, y, z;};
            T points[POINTS_3D];
        };

        Point3D<T>() : x(0), y(0), z(0) {}
        Point3D<T>(T x0, T y0, T z0) : x(x0), y(y0), z(z0) {}
        inline Point3D<T> operator+(const Point3D<T>& point) const
        {
            return {this.x + point.x, this.y + point.y, this.z + point.z};
        }

        inline Point3D<T> operator-(const Point3D<T>& point) const
        {
            return {this.x - point.x, this.y - point.y, this.z - point.z};
        }

        inline Point3D<T> operator*(const float& factor) const
        {
            return {this.x*factor, this.y*factor, this.z*factor};
        }

        inline T operator*(const Point3D<T>& point) const
        {
            return {this.x*point.x + this.y*point.y+this.z*point.z};
        }

        inline Point3D<T> operator ^(const Point3D<T> &point) const
        {
            return {y*point.z-z*point.y, z*point.x-x*point.z, x*point.y-y*point.x};
        }

        template <typename > friend std::ostream& operator<<(std::ostream& out, const Point3D<T>& p);

    };

    using Point2Di = Point2D<int>;
    using Point2Df = Point2D<float>;
    using Point3Di = Point3D<int>;
    using Point3Df = Point3D<float>;

} // namespace tr
