#ifndef CONSTANTS_H
#define CONSTANTS_H


#include "./math/math.h"
#include "./raytracer/raytracer.h"

#include <limits>
#include <memory>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>

using std::cerr;
using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;
using std::vector;
using std::chrono::duration;
using std::chrono::steady_clock;

using namespace raytracer;
using math::clamp;
using math::Color;
using math::random;
using math::Vector3;


#endif