#pragma once

#include "geometry.hpp"
#include "sphere.hpp"

void Render(std::vector<Sphere> &spheres);

Vec3f CastRay(const Vec3f &origin, const Vec3f &direction, const std::vector<Sphere> &spheres);

bool SceneIntersect(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material &material);