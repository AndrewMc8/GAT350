#pragma once
#include "Material.h"

class Geometry
{
public:
    Geometry() = default;
    virtual ~Geometry() = default;

    virtual bool Hit(const ray_t& r, float tMin, float tMax, rayCastHit_t& hit) = 0;

    std::shared_ptr<Material> material;

    Geometry(std::shared_ptr<Material> material) : material{ material } {}
};
