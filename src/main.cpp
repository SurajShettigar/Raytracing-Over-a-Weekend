#include "constants.h"

#include "./utils/camera.h"
#include "./utils/image.h"
#include "./geo/sphere.h"
#include "./geo/geometry_list.h"
#include "./material/lambert.h"
#include "./material/metallic.h"
#include "./material/dielectric.h"

#include <chrono>

using std::chrono::duration;
using std::chrono::steady_clock;

using namespace raytracer;
using math::random;
using math::clamp;
using math::Color;
using math::Vector3;

Color getRayPixelColor(const Ray &ray, const Geometry &geo, int currBounce)
{
    raytracer::HitInfo hit;

    if(currBounce <= 0)
        return Color::zero;

    if (geo.isHit(ray, 0.001, INFINITY, hit))
    {
        Color color = Color::zero;
        Ray outRay;
        // // Color color = (hit.normal + Vector3::one) * 0.5;
        // // return color;
        if(hit.material->scatterRay(ray, hit, color, outRay))
            return color * getRayPixelColor(outRay, geo, --currBounce);
        else
            return Color::zero;

        // return 0.5 * getRayPixelColor(Ray(hit.point, Vector3::randomHemiSpherical(hit.normal)), geo, --currBounce);
    }

    Vector3 normalizedDir = Vector3::normalize(ray.direction);
    normalizedDir = (normalizedDir + Vector3::one) / 2.0;
    return Vector3::lerp(Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0), normalizedDir.y);
}

void writeColorToFile(std::ostream &out, Color color, int samples)
{
    color /= samples;

    // Gamma correction with gamma 2
    color.x = sqrt(color.x);
    color.y = sqrt(color.y);
    color.z = sqrt(color.z);

    out << static_cast<int>(clamp(color.x, 0.0, 0.999) * 256)
        << ' ' << static_cast<int>(clamp(color.y, 0.0, 0.999) * 256)
        << ' ' << static_cast<int>(clamp(color.z, 0.0, 0.999) * 256) << '\n';
}

void renderImage()
{
    Camera camera(50.0, 16.0 / 9.0, 1.0);
    camera.position = Point::zero;
    Image image(640, 360);
    image.samplesPerPixel = 16;
    image.maxBounces = 12;

    shared_ptr<Lambert> matLambert = make_shared<Lambert>(Color(1.0, 0.7, 0.3));
    shared_ptr<Metallic> matMetallic = make_shared<Metallic>(Color(0.8, 0.8, 0.8), 0.25);
    shared_ptr<Dielectric> matGlass = make_shared<Dielectric>(Color(1.0, 1.0, 1.0), 1.51);

    GeometryList geoList;
    geoList.add(make_shared<Sphere>(100.0, Point(0.0, -100.5, -2.0), matLambert));
    geoList.add(make_shared<Sphere>(0.5, Point(-1.0, 0.0, -2.0), matLambert));
    geoList.add(make_shared<Sphere>(0.5, Point(0.0, 0.0, -2.0), matMetallic));
    geoList.add(make_shared<Sphere>(0.5, Point(1.0, 0.0, -2.0), matGlass));

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
                color += getRayPixelColor(camera.getRay(u, v), geoList, image.maxBounces);
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