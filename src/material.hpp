#pragma once

#include "geometry.hpp"

struct Material
{
    Material(const Vec3f &albedo, const Vec3f &color, const float &specular) : Albedo(albedo), DiffuseColor(color), Specular(specular) {}
    Material() : Albedo(1, 0, 0), DiffuseColor(), Specular() {}
    Vec3f Albedo;
    Vec3f DiffuseColor;
    float Specular;
};
