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
using math::clamp;
using math::Color;
using math::random;
using math::Vector3;

Color getRayPixelColor(const Ray &ray, const Geometry &geo, int currBounce)
{
    raytracer::HitInfo hit;

    if (currBounce <= 0)
        return Color::zero;

    if (geo.isHit(ray, 0.0001, INFINITY, hit))
    {
        Color color = Color::zero;
        Ray outRay;

        if (hit.material->scatterRay(ray, hit, color, outRay))
            return color * getRayPixelColor(outRay, geo, --currBounce);
        else
            return Color::zero;
    }

    /// Color the background
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

void renderImage(const Camera &camera, const Image &image, const GeometryList &geoList)
{
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

Camera getCamera()
{
    return Camera(25.0,                     // FOV
                  16.0 / 9.0,               // Aspect Ratio
                  13.0,                     // Focus Distance
                  0.25,                      // Aperture
                  Point(8.0, 2.5, 7.0),     // Camera position
                  Point(0.0, 0.0, -10.0)); // Look At position
}

Image getTargetImage()
{
    Image image(640, 360);
    image.samplesPerPixel = 142;
    image.maxBounces = 8;

    return image;
}

GeometryList getRandomScene()
{
    shared_ptr<Material> groundMat = make_shared<Lambert>(Color::one * 0.5);

    GeometryList geoList;

    // Create ground
    geoList.add(make_shared<Sphere>(1000.0, Point(0.0, -1000.0, 0.0), groundMat));
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            double randMat = random();
            shared_ptr<Material> mat = groundMat;
            if (randMat < 0.2)
                mat = make_shared<Dielectric>(Color::one, 1.51);
            else if (randMat < 0.4)
                mat = make_shared<Metallic>(Color::random(0.8, 1.0), random(0.025, 0.65));
            else
                mat = make_shared<Lambert>(Color::random(0.3, 1.0));

            double randRadius = random(0.25, 1.0);
            if(random() < 0.7)
                randRadius = random(0.25, 0.5);
            else
                randRadius = random(0.75, 1.0);

            double randXPos = math::mapRange(static_cast<double>(x), 0.0, 8.0, -10.0, 10.0);
            randXPos += random(-randRadius / 2.0, randRadius / 2.0);
            double randZPos = math::mapRange(static_cast<double>(y), 0.0, 8.0, 0.0, -20.0);
            randZPos += random(-randRadius / 2.0, randRadius / 2.0);
            Point pos = Point(randXPos, randRadius, randZPos);

            shared_ptr<Sphere> randSphere = make_shared<Sphere>(randRadius, pos, mat);
            geoList.add(randSphere);
        }
    }

    return geoList;
}

int main(int argc, char **argv)
{
    auto start = steady_clock::now();

    renderImage(getCamera(), getTargetImage(), getRandomScene());

    auto end = steady_clock::now();
    duration<double> elapsed = end - start;

    cerr << endl
         << "Time taken to render: " << elapsed.count() << "s" << endl;

    return 0;
}