#include "render.hpp"

#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>

void Render(std::vector<Sphere> &spheres, const std::vector<Light> &lights)
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
            frameBuffer[i + j * width] = CastRay(Vec3f(0, 0, 0), dir, spheres, lights);
        }
    }

    std::ofstream ofs;
    ofs.open("render.ppm", std::ofstream::out | std::ofstream::binary);
    ofs << "P6\n"
        << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height * width; ++i)
    {
        Vec3f &c = frameBuffer[i];
        float max = std::max(c[0], std::max(c[1], c[2]));
        if (max > 1)
            c = c * (1. / max);

        for (size_t j = 0; j < 3; j++)
        {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, frameBuffer[i][j])));
        }
    }
    ofs.close();
}

Vec3f CastRay(const Vec3f &origin, const Vec3f &direction, const std::vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    Vec3f point, N;
    Material material;

    if (!SceneIntersect(origin, direction, spheres, point, N, material))
        return Vec3f(0.2, 0.7, 0.8);

    float diffuseLightIntensity = 0;
    float specularLightIntensity = 0;
    for (auto light : lights)
    {
        Vec3f lightDirection = (light.Position - point).normalize();
        diffuseLightIntensity += light.Intensity * std::max(0.0f, lightDirection * N);
        specularLightIntensity += powf(std::max(0.f, -Reflect(-lightDirection, N) * direction), material.Specular) * light.Intensity;
    }

    return material.DiffuseColor * diffuseLightIntensity * material.Albedo[0] + Vec3f(1., 1., 1.) * specularLightIntensity * material.Albedo[1];
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

Vec3f Reflect(const Vec3f &I, const Vec3f &N)
{
    return I - N * 2.f * (I * N);
}
