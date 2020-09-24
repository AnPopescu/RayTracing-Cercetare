#pragma once
#include "..//glm/ext/vector_float3.hpp"

class Ray
{	public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() {};
	Ray(const glm::vec3& origin, const glm::vec3& dir):origin(origin),direction(dir){}
	glm::vec3 getOrigin() { return this->origin; }
	glm::vec3 getDirection() { return this->direction; }
	glm::vec3 ray_at_point(float t) const;

};

