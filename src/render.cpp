#include "render.hpp"

#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>

void Render(std::vector<Sphere> &spheres)
{
    const int width = 1024;
    const int height = 768;
    const int fov = 90;

    std::vector<Vec3f> frameBuffer(width * height);

    for (size_t j = 0; j < height; ++j)
    {
        for (size_t i = 0; i < width; ++i)
        {
            float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            frameBuffer[i + j * width] = CastRay(Vec3f(0, 0, 0), dir, spheres);
        }
    }

    std::ofstream ofs;
    ofs.open("render.ppm", std::ofstream::out | std::ofstream::binary);
    ofs << "P6\n"
        << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height * width; ++i)
    {
        for (size_t j = 0; j < 3; j++)
        {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, frameBuffer[i][j])));
        }
    }
    ofs.close();
}

Vec3f CastRay(const Vec3f &origin, const Vec3f &direction, const std::vector<Sphere> &spheres)
{
    Vec3f point, N;
    Material material;

    if (!SceneIntersect(origin, direction, spheres, point, N, material))
        return Vec3f(0.2, 0.7, 0.8);

    return material.Color;
}

bool SceneIntersect(const Vec3f &origin, const Vec3f &direction, const std::vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material &material)
{
    float sphereDistance = std::numeric_limits<float>::max();
    for (auto sphere : spheres)
    {
        float distance;
        if (sphere.IsRayIntersecting(origin, direction, distance) && distance < sphereDistance)
        {
            sphereDistance = distance;
            hit = origin + direction * distance;
            N = (hit - sphere.GetCenter()).normalize();
            material = sphere.GetMaterial();
        }
    }
    return sphereDistance < 1000;
}
