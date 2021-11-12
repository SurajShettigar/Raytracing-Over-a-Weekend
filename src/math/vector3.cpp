#include "vector3.h"

namespace raytracer
{
    namespace math
    {
        Vector3::Vector3(const Vector3 &w)
        {
            v[0] = w[0];
            v[1] = w[1];
            v[2] = w[2];
        }

        Vector3 &Vector3::operator=(const Vector3 &w)
        {
            v[0] = w[0];
            v[1] = w[1];
            v[2] = w[2];
            return *this;
        }

        Vector3 Vector3::operator-() const
        {
            return Vector3(-v[0], -v[1], -v[2]);
        }

        Vector3 &Vector3::operator+=(const Vector3 &w)
        {
            v[0] += w[0];
            v[1] += w[1];
            v[2] += w[2];

            return *this;
        }
        Vector3 &Vector3::operator-=(const Vector3 &w)
        {
            v[0] -= w[0];
            v[1] -= w[1];
            v[2] -= w[2];
            return *this;
        }

        Vector3 &Vector3::operator*=(const double a)
        {
            v[0] *= a;
            v[1] *= a;
            v[2] *= a;
            return *this;
        }

        Vector3 &Vector3::operator/=(const double a)
        {
            return *this *= 1 / a;
        }

        // Vector specific operations
        double Vector3::length() const
        {
            return sqrt(lengthSquared());
        }

        double Vector3::lengthSquared() const
        {
            return (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
        }

        Vector3 Vector3::normalize() const
        {
            return (*this / length());
        }

        double Vector3::dot(const Vector3 &v, const Vector3 &w)
        {
            return (v[0] * w[0] + v[1] * w[1] + v[2] * w[2]);
        }

        Vector3 Vector3::cross(const Vector3 &v, const Vector3 &w)
        {
            return Vector3(v[1] * w[2] - v[2] * w[1],
                           v[2] * w[0] - v[0] * w[2],
                           v[0] * w[1] - v[1] * w[0]);
        }

        Vector3 Vector3::normalize(const Vector3 &v)
        {
            return v / v.length();
        }

        Vector3 Vector3::lerp(const Vector3 &v, const Vector3 &w, double t)
        {
            return (1 - t) * v + t * w;
        }
        
        Vector3 Vector3::reflect(const Vector3& v, const Vector3 & normal)
        {
            return v - 2 * dot(v, normal) * normal;
        }

        // Arithmetic Operations
        Vector3 operator+(const Vector3 &v, const Vector3 &w)
        {
            return Vector3(v[0] + w[0], v[1] + w[1], v[2] + w[2]);
        }

        Vector3 operator-(const Vector3 &v, const Vector3 &w)
        {
            return Vector3(v[0] - w[0], v[1] - w[1], v[2] - w[2]);
        }

        Vector3 operator*(const Vector3 &v, const Vector3 &w)
        {
            return Vector3(v[0] * w[0], v[1] * w[1], v[2] * w[2]);
        }

        Vector3 operator*(double a, const Vector3 &v)
        {
            return Vector3(v[0] * a, v[1] * a, v[2] * a);
        }

        Vector3 operator*(const Vector3 &v, double a)
        {
            return a * v;
        }

        Vector3 operator/(const Vector3 &v, double a)
        {
            return (1 / a) * v;
        }

        // Other operations
        Vector3 Vector3::random()
        {
            return Vector3(raytracer::math::random(),
                           raytracer::math::random(),
                           raytracer::math::random());
        }

        Vector3 Vector3::random(double min, double max)
        {
            return Vector3(raytracer::math::random(min, max),
                           raytracer::math::random(min, max),
                           raytracer::math::random(min, max));
        }

        Vector3 Vector3::randomSpherical()
        {
            double theta = 2 * PI * raytracer::math::random();
            double phi = acos(1 - 2 * raytracer::math::random());

            return Vector3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi)).normalize();
        }

        Vector3 Vector3::randomHemiSpherical(const Vector3 &normal)
        {
            Vector3 rand = Vector3::randomSpherical();
            if (Vector3::dot(rand, normal) > 0.0)
                return rand;
            else
                return -rand;
        }

        std::ostream &operator<<(std::ostream &out, const Vector3 &v)
        {
            return out << '{' << v[0] << ", " << v[1] << ", " << v[2] << '}';
        }

        // Comparison operations
        bool operator==(const Vector3 &v, const Vector3 &w)
        {
            return std::abs(v.length() - w.length()) <= std::numeric_limits<float>::epsilon();
        }

        const Vector3 Vector3::zero{0.0, 0.0, 0.0};
        const Vector3 Vector3::one{1.0, 1.0, 1.0};
        const Vector3 Vector3::up{0.0, 1.0, 0.0};
        const Vector3 Vector3::down{0.0, -1.0, 0.0};
        const Vector3 Vector3::left{-1.0, 0.0, 0.0};
        const Vector3 Vector3::right{1.0, 0.0, 0.0};
        const Vector3 Vector3::forward{0.0, 0.0, 1.0};
        const Vector3 Vector3::back{0.0, 0.0, -1.0};
    }
}
