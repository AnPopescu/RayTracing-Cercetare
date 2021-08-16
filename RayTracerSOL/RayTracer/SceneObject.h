#pragma once

#define GLM_FORCE_CTOR_INIT
#define OUT
#include "glm.hpp"

struct Material
{
	glm::vec3 color;
	float diffuse = 0;
	float reflect = 0;
	float refract = 0;
	int specular = 0;
	int shininess= 0;

	float kd = 0;
	float ks = 0;
};

struct Transform
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};

struct HitInfo
{
	glm::vec3 normal;
	float t = 0 ;
	glm::vec3 finalColor;
};

class SceneObject
{	

protected:
	Transform transform;
	Material material;

	virtual bool TestIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, OUT HitInfo& hit ) = 0;
};
