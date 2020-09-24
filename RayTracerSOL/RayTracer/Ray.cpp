#include "Ray.h"
#include <iostream>

glm::vec3 Ray::ray_at_point(float t) const
{
	if (t == 0) return origin; // ?
	if (t < 0) {
		std::cout << "Ray moving backwards? \n";
		return origin;
	}
	return origin + t*direction;
}
