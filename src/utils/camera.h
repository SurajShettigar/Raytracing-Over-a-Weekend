#ifndef CAMERA_H
#define CAMERA_H

#include "../math/vector3.h"
#include "ray.h"

namespace raytracer
{
    using math::Point;

    class Camera
    {
    private:
        float m_aspectRatio = 16.0 / 9.0;
        float m_viewportWidth = 2.0;
        float m_viewportHeight = 1.125;
        float m_focalLength = 1.0;

        Point lowerLeftCorner = position 
                                  - (Vector3::right * m_viewportWidth / 2.0) 
                                  - (Vector3::up * m_viewportHeight / 2.0) 
                                  - (Vector3::forward * m_focalLength);

    public:
        const float &aspectRatio = m_aspectRatio;
        const float &viewportWidth = m_viewportWidth;
        const float &viewportHeight = m_viewportHeight;
        const float &focalLength = m_focalLength;

        Point position = Point::zero;

        Camera(float viewportWidth, float viewportHeight, float focalLength)
            : m_aspectRatio{viewportWidth / viewportHeight},
              m_viewportWidth{viewportWidth},
              m_viewportHeight{viewportHeight},
              m_focalLength{focalLength} {}

        // Returns a ray from the given uv co-ordinates
        Ray getRay(double u, double v) const
        {
            return Ray(position,
                       lowerLeftCorner 
                       + u * Vector3::right * viewportWidth 
                       + v * Vector3::up * viewportHeight 
                       - position);
        }
    };
}

#endif