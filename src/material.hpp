#pragma once

#include "geometry.hpp"

struct Material
{
    Material(const Vec2f &albedo, const Vec3f &color, const float &specular) : Albedo(albedo), DiffuseColor(color), Specular(specular) {}
    Material() : DiffuseColor() {}
    Vec2f Albedo;
    Vec3f DiffuseColor;
    float Specular;
};
