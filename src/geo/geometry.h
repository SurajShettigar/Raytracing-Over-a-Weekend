#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../utils/ray.h"
#include "../math/vector3.h"

namespace raytracer
{
    class Geometry
    {
    private:
    public:
        Geometry() = default;
        virtual bool isHit(const Ray& ray) const {}
    };
}

#endif