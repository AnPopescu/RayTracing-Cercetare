#pragma once
//#include "..\\glm\glm.hpp"
#include "..\\glm\exponential.hpp"
#include "..\glm\common.hpp"
#include "..\glm\vec3.hpp"
#include "hitable.h"

class Sphere: public hitable
{
	public:

	glm::vec3 center;
	float radius;
	Sphere(glm::vec3 center, float radius):center(center),radius(radius){}

	bool hit(const Ray& r, hit_record &rec);
};

