#ifndef GEOMETRY_LIST_H
#define GEOMETRY_LIST_H

#include <vector>
#include <memory>

#include "geometry.h"

using std::shared_ptr;
using std::vector;

namespace raytracer
{
    class GeometryList : public Geometry
    {
    private:
        vector<shared_ptr<Geometry>> geoList;

    public:
        GeometryList() = default;
        GeometryList(shared_ptr<Geometry> geo) { add(geo); }

        void clear();
        void add(shared_ptr<Geometry> geo);
        bool isHit(const Ray &ray, double tMin, double tMax, HitInfo &hitInfo) const override;
    };
}

#endif