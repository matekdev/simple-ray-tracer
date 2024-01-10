#pragma once

#include "geometry.hpp"

struct Material
{
    Material(const Vec3f &color) : Color(color) {}
    Material() : Color() {}
    Vec3f Color;
};