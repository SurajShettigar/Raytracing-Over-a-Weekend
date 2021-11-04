#ifndef RAY_H
#define RAY_H

#include "../math/vector3.h"

namespace raytracer
{
    using math::Point;
    using math::Vector3;

    class Ray
    {
    private:
        Point m_origin;
        Vector3 m_direction;

    public:
        Ray(const Point &origin, const Vector3 &direction)
            : m_origin{origin}, m_direction{direction} {}

        Point &origin = m_origin;
        Vector3 &direction = m_direction;

        Point getPointAtDistance(double dist) const;
    };
}

#endif