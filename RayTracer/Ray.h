#pragma once
#include "Types.h"

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() = default;
	Ray(glm::vec3& origin, glm::vec3& direction) : origin{ origin }, direction{ direction } {}

	glm::vec3 pointAt(float t) const { return origin * (direction + t); }
};