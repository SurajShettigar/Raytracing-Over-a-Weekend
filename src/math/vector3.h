#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

namespace raytracer
{
    namespace math
    {

        class Vector3
        {
        private:
            double v[3]{0, 0, 0};

        public:
            // Constructors
            Vector3() = default;
            Vector3(double x = 0.0, double y = 0.0, double z = 0.0) : v{x, y, z} {}

            // Access and assigments
            Vector3(const Vector3 &w);
            Vector3 &operator=(const Vector3 &w);

            double &x = v[0];
            double &y = v[1];
            double &z = v[2];

            double operator[](int i) const { return v[i]; }
            double &operator[](int i) { return v[i]; }

            // Current Vector operations
            Vector3 operator-() const;
            Vector3 &operator+=(const Vector3 &w);
            Vector3 &operator-=(const Vector3 &w);
            Vector3 &operator*=(const double a);
            Vector3 &operator/=(const double a);

            // Vector Specific operataions
            double length() const;
            double lengthSquared() const;
            Vector3 normalize() const;

            static double dot(const Vector3 &v, const Vector3 &w);
            static Vector3 cross(const Vector3 &v, const Vector3 &w);
            static Vector3 normalize(const Vector3 &v);

            // Arithmetic operations
            friend Vector3 operator+(const Vector3 &v, const Vector3 &w);
            friend Vector3 operator-(const Vector3 &v, const Vector3 &w);
            friend Vector3 operator*(const Vector3 &v, const Vector3 &w);
            friend Vector3 operator*(const Vector3 &v, const double a);
            friend Vector3 operator*(const double a, const Vector3 &v);
            friend Vector3 operator/(const Vector3 &v, const double a);

            // Other operations
            friend std::ostream &operator<<(std::ostream &out, const Vector3 &v);

            // Comparison operations
            friend bool operator==(const Vector3& v, const Vector3& w);

            // static values
            static const Vector3 zero;
            static const Vector3 one;
            static const Vector3 up;
            static const Vector3 down;
            static const Vector3 left;
            static const Vector3 right;
            static const Vector3 forward;
            static const Vector3 back;
        };

        using Point = Vector3;
        using Color = Vector3;
    }
}

#endif