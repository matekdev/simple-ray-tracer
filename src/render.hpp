#pragma once

#include "geometry.hpp"
#include "sphere.hpp"
#include "light.hpp"

void Render(std::vector<Sphere> &spheres, const std::vector<Light> &lights);

Vec3f CastRay(const Vec3f &origin, const Vec3f &direction, const std::vector<Sphere> &spheres, const std::vector<Light> &lights, size_t depth = 0);

bool SceneIntersect(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material &material);

Vec3f Reflect(const Vec3f &I, const Vec3f &N);