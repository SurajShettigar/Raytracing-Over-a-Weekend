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
        float m_fov = 60.0;
        float m_focalLength = 1.0;
        float m_aspectRatio = 16.0 / 9.0;
        float m_viewportHeight = 1.125;
        float m_viewportWidth = 2.0;

        Point lowerLeftCorner = position - (Vector3::right * m_viewportWidth / 2.0) - (Vector3::up * m_viewportHeight / 2.0) - (Vector3::forward * m_focalLength);

    public:
        const float &fov = m_fov;
        const float &aspectRatio = m_aspectRatio;
        const float &focalLength = m_focalLength;
        const float &viewportHeight = m_viewportHeight;
        const float &viewportWidth = m_viewportWidth;

        Point position = Point::zero;

        Camera(float fov, float aspectRatio, float focalLength)
            : m_fov{fov},
              m_aspectRatio{aspectRatio},
              m_focalLength{focalLength},
              m_viewportHeight{static_cast<float>(2.0 * tan(math::degreeToRadians(fov) / 2.0))},
              m_viewportWidth{m_aspectRatio * m_viewportHeight} {}

        // Returns a ray from the given uv co-ordinates
        Ray getRay(double u, double v) const
        {
            return Ray(position,
                       lowerLeftCorner + u * Vector3::right * viewportWidth + v * Vector3::up * viewportHeight - position);
        }
    };
}

#endif