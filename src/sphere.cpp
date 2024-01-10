#include "sphere.hpp"

bool Sphere::IsRayIntersecting(const Vec3f &origin, const Vec3f &direction, float &t0)
{
    Vec3f L = _center - origin;
    float tca = L * direction;
    float d2 = L * L - tca * tca;
    if (d2 > _radius * _radius)
        return false;
    float thc = sqrtf(_radius * _radius - d2);
    t0 = tca - thc;
    float t1 = tca + thc;
    if (t0 < 0)
        t0 = t1;
    if (t0 < 0)
        return false;
    return true;
}

Vec3f Sphere::GetCenter()
{
    return _center;
}

Material Sphere::GetMaterial()
{
    return _material;
}