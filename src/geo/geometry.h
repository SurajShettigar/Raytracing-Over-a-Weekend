#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../utils/ray.h"
#include "../math/vector3.h"

#include <cmath>

namespace raytracer
{
    struct HitInfo
    {
        Point point = Point::zero;
        Vector3 normal = Point::zero;
        double distInRay = -1.0;
        bool isFrontFace = true;

        inline void setFaceNormal(const Vector3& rayDir, const Vector3& outwardNormal)
        {
            isFrontFace = Vector3::dot(rayDir, outwardNormal) < 0.0;
            normal = isFrontFace ? outwardNormal : -outwardNormal;
        }
    };
    

    class Geometry
    {
    private:
    public:
        Geometry() = default;
        virtual bool isHit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) const {}
    };
}

#endif