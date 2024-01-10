#pragma once

#include "geometry.hpp"
#include "material.hpp"

class Sphere
{
public:
    Sphere(const Vec3f &center, const float &radius, const Material &material) : _center(center), _radius(radius), _material(material) {}

    bool IsRayIntersecting(const Vec3f &origin, const Vec3f &direction, float &t0);
    Vec3f GetCenter();
    Material GetMaterial();

private:
    Vec3f _center;
    float _radius;
    Material _material;
};