#pragma once

#include "geometry.hpp"

struct Light
{
    Light(const Vec3f &position, const float &intensity) : Position(position), Intensity(intensity) {}
    Vec3f Position;
    float Intensity;
};
