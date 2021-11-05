#include "constants.h"

#include "./math/vector3.h"
#include "./utils/ray.h"
#include "./utils/camera.h"
#include "./utils/image.h"
#include "./geo/sphere.h"
#include "./geo/geometry_list.h"

#include <chrono>

using std::chrono::duration;
using std::chrono::steady_clock;

using namespace raytracer;
using raytracer::math::Color;
using raytracer::math::Vector3;

Color getRayPixelColor(const Ray &ray, const Geometry &geo)
{
    HitInfo hit;
    if (geo.isHit(ray, 0.0, INFINITY, hit))
    {
        Color color = (hit.normal + Vector3::one) * 0.5;
        return color;
    }

    Vector3 normalizedDir = Vector3::normalize(ray.direction);
    normalizedDir = (normalizedDir + Vector3::one) / 2.0;
    return Vector3::lerp(Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0), normalizedDir.y);
}

void writeColorToFile(std::ostream &out, Color color, int samples)
{
    color /= samples;

    out << static_cast<int>(clamp(color.x, 0.0, 0.999) * 256)
        << ' ' << static_cast<int>(clamp(color.y, 0.0, 0.999) * 256)
        << ' ' << static_cast<int>(clamp(color.z, 0.0, 0.999) * 256) << '\n';
}

void renderImage()
{
    Camera camera(2.0, 1.125, 1.0);
    camera.position = Point::zero;
    Image image(640, 360);
    image.samplesPerPixel = 1;

    GeometryList geoList;
    geoList.add(make_shared<Sphere>(100.0, Point(0.0, -100.5, -1.0)));

    geoList.add(make_shared<Sphere>(0.65, Point(0.5, 0.0, -1.0)));

    Color color(1.0, 1.0, 1.0);

    cout << "P3\n"
         << image.width << ' ' << image.height << "\n255\n";
    for (int y = image.height - 1; y >= 0; --y)
    {
        cerr << "Rendering image... Progress: " << ((1 - y / (image.height - 1.0)) * 100.0) << " %\r" << std::flush;

        for (int x = 0; x < image.width; ++x)
        {
            color = Color::zero;
            for (int s = 0; s < image.samplesPerPixel; s++)
            {
                double u = (x + random()) / (image.width - 1);
                double v = (y + random()) / (image.height - 1);
                color += getRayPixelColor(camera.getRay(u, v), geoList);
            }
            writeColorToFile(cout, color, image.samplesPerPixel);
        }
    }
}

int main(int argc, char **argv)
{
    auto start = steady_clock::now();

    renderImage();

    auto end = steady_clock::now();
    duration<double> elapsed = end - start;

    cerr << endl
         << "Time taken to render: " << elapsed.count() << "s" << endl;

    return 0;
}