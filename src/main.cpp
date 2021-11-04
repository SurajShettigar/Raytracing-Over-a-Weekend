#include <iostream>

#include "./math/vector3.h"
#include "./utils/ray.h"
#include "./utils/camera.h"
#include "./utils/image.h"
#include "./geo/sphere.h"

using std::cerr;
using std::cout;
using std::endl;

using namespace raytracer;
using raytracer::math::Color;
using raytracer::math::Vector3;

Sphere sphere(0.25, Point(0.0, 0.0, -0.75));

Color getRayPixelColor(const Ray &ray)
{
    if(sphere.isHit(ray))
        return Color(1.0, 0.0, 0.0);

    Vector3 normalizedDir = Vector3::normalize(ray.direction);
    normalizedDir = (normalizedDir + Vector3::one) / 2.0;
    return Vector3::lerp(Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0), normalizedDir.y);
}

int main(int argc, char **argv)
{
    Camera camera(2.0, 1.125, 1.0);
    Image image(640, 360);

    Ray ray(Vector3::zero, Vector3::back);
    Color color(1.0, 1.0, 1.0);
    Vector3 lowerLeftCorner = Vector3::zero - (Vector3::right * camera.viewportWidth / 2.0) - (Vector3::up * camera.viewportHeight / 2.0) - (Vector3::forward * camera.focalLength);

    cout << "P3\n"
         << image.width << ' ' << image.height << "\n255\n";
    for (int y = image.height - 1; y >= 0; --y)
    {
        cerr << "Rendering image... Progress: " << ((1 - y / (image.height - 1.0)) * 100.0) << '%' << '\r' << std::flush;
        for (int x = 0; x < image.width; ++x)
        {
            double nx = static_cast<double>(x) / static_cast<double>(image.width - 1);
            double ny = static_cast<double>(y) / static_cast<double>(image.height - 1);

            ray.direction = lowerLeftCorner + nx * Vector3::right * camera.viewportWidth + ny * Vector3::up * camera.viewportHeight - camera.position;
            color = getRayPixelColor(ray);
            cout << static_cast<int>(color.x * 255.999)
                 << ' ' << static_cast<int>(color.y * 255.999)
                 << ' ' << static_cast<int>(color.z * 255.999) << '\n';
        }
    }
    return 0;
}