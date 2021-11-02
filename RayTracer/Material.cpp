#include "Material.h"

bool Lambertian::Scatter(const ray_t& ray, const rayCastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const
{
    glm::vec3 direction = glm::normalize(hit.normal + randomInUnitSphere()); //<generate a normalized direction by create a vector that points to the target from the hit.point, normalize the result>

    scattered = { hit.point, direction };
    attenuation = albedo;

    return true;
}

bool Metal::Scatter(const ray_t& ray, const rayCastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const
{
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

    scattered.origin = hit.point;
    scattered.direction = reflected + (randomInUnitSphere() * fuzz);
    attenuation = albedo;

    return glm::dot(scattered.direction, hit.normal) > 0;
}