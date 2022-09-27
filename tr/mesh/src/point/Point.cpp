#include "point/Point.hpp"

namespace tr
{
    template <typename T> std::ostream& operator<<(std::ostream& out, const Point2D<T>& p)
    {
        std::string output{"("+std::to_string(p.x) + "," + std::to_string(p.y) + ")\n"};
        out << output;
        return out;
    }

    template <typename T> std::ostream& operator<<(std::ostream& out, const Point3D<T>& p)
    {
        std::string output{"("+std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z) + ")\n"};
        out << output;
        return out;
    }
} // namespace tr
