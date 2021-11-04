// #include <iostream>

// #include "../math/vector3.h"
// #include "../utils/ray.h"
// #include "../utils/camera.h"
// #include "../utils/image.h"

// using std::cerr;
// using std::cout;
// using std::endl;

// using namespace raytracer;
// using raytracer::math::Color;
// using raytracer::math::Vector3;

// Color getRayPixelColor(const Ray& ray)
// {
//     Vector3 normalizedDir = ray.direction.normalize();
//     normalizedDir = normalizedDir * 0.5 + 0.5;
//     return Vector3::lerp(Color(1.0, 1.0, 1.0), Color(0.0, 1.0, 0.0), normalizedDir.y);
// }

// int main(int argc, char **argv)
// {
//     Camera camera(2.0, 1.125, 1.0);
//     Image image(640, 360);

//     Ray ray(Vector3::zero, Vector3::back);
//     Color color(1.0, 1.0, 1.0);
//     Vector3 lowerLeftCorner = Vector3::zero 
//                               - (Vector3::right * camera.viewportWidth) 
//                               - (Vector3::up * camera.viewportHeight) 
//                               - (Vector3::forward * camera.focalLength);

//     cout << "P3\n" << image.width << ' ' << image.height << "\n255\n";
//     for (int y = image.height - 1; y >= 0; --y)
//     {
//         cerr << "Rendering image... Progress: " << ((1 - y / (image.height - 1.0)) * 100.0) << '%' << std::flush;
//         for (int x = 0; x < image.width; ++x)
//         {
//             double nx = static_cast<double>(x) / (image.width - 1);
//             double ny = static_cast<double>(y) / (image.height - 1);

//             ray.direction = lowerLeftCorner 
//                             + nx * Vector3::right * camera.viewportWidth 
//                             + ny * Vector3::up * camera.viewportHeight 
//                             - camera.position;
//             color = getRayPixelColor(ray);
//             cout << static_cast<int>(color.x * 255.99) 
//                  << ' ' << static_cast<int>(color.y * 255.99) 
//                  << ' ' << static_cast<int>(color.z * 255.99) << '\n';
//         }
//     }
//     return 0;
// }