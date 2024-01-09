#include "render.hpp"
#include "geometry.hpp"

#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>

void Render(const int &width, const int &height)
{
    std::vector<Vec3f> frameBuffer(width * height);

    for (size_t i = 0; i < height; ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            frameBuffer[j + i * width] = Vec3f(i / float(height), j / float(width), 0);
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
