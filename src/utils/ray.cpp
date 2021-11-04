#include "ray.h"

using namespace raytracer;

Point Ray::getPointAtDistance(double t) const
{
    return m_origin + t * m_direction;
}