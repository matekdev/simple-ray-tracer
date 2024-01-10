#include "render.hpp"

int main()
{
    Material ivory(Vec3f(0.4, 0.4, 0.3));
    Material red(Vec3f(0.3, 0.1, 0.1));

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2, ivory));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red));
    spheres.push_back(Sphere(Vec3f(1.5, -0.5, -18), 3, red));
    spheres.push_back(Sphere(Vec3f(7, 5, -18), 4, ivory));

    Render(spheres);
}
