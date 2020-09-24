#pragma once
#include "Ray.h"

struct hit_record
{	
	float t;
	glm::vec3 intersectPoint;
	glm::vec3 intersectNormal;
};

class hitable
{
};

