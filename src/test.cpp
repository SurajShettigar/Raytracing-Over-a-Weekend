#include <iostream>
#include "math/vector3.h"

using std::cout;
using std::endl;

using namespace raytracer::math;

int main(int argc, char **argv)
{
    const int IMG_WIDTH = 512;
    const int IMG_HEIGHT = 512;
    int abc = 10.0f;

    Vector3 v(1.0, 1.0, 3.0);


    cout << "V.x = " << v.x << endl;
    v.x = abc;
    cout << "V.x = " << v.x << endl;
    v.x = 25.0f;
    cout << "V.x = " << v.x << endl;
    cout << "abc = " << abc << endl;

    double a = v[0];
    v[0] = 25.0;
    cout << "a = " << a << endl;
    cout << "v[0] = " << v[0] << endl;
    cout << "v.x = " << v.x << endl;

    Vector3 b = v;
    cout << "B: " << b << endl;
    cout << "V: " << v << endl;
    v *= 23.645;
    cout << "B: " << b << endl;
    cout << "V: " << v.normalize() << endl;

    v = Vector3(0.0, 0.9999999999999999, 0.001);
    Vector3 w(0.0, 1.0, 0.001);

    cout << (v == w) << endl;

    // cout << "P3\n"
    //      << IMG_WIDTH << " " << IMG_HEIGHT
    //      << "\n255\n";

    // for (int y = IMG_HEIGHT - 1; y >= 0; y--)
    // {
    //     for (int x = 0; x < IMG_WIDTH; x++)
    //     {
    //         float r = static_cast<float>(x) / (IMG_WIDTH - 1);
    //         float g = static_cast<float>(y) / (IMG_HEIGHT - 1);
    //         float b = 0.0f;

    //         int ir = static_cast<int>(r * 255.0f);
    //         int ig = static_cast<int>(g * 255.0f);
    //         int ib = static_cast<int>(b * 255.0f);
    //         cout << ir << ' ' << ig << ' ' << ib << '\n';
    //     }
    // }
    return 0;
}