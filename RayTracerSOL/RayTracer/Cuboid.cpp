#include "Cuboid.h"
#include <iostream>
#include <algorithm>



Cuboid::Cuboid(glm::vec3 corner1, glm::vec3 corner2)
{
	if (corner1.x == corner2.x || corner1.y == corner2.y || corner1.z == corner2.z)
	{
		std::cout << "CUBOID IS PLANE OR POINT" << std::endl;
	}

	transform.Position.x = abs(corner2.x - corner1.x) / 2;
	transform.Position.y = abs(corner2.y - corner1.y) / 2;
	transform.Position.z = abs(corner2.z - corner1.z) / 2;

	firstCorner = corner1;
	secondCorner = corner2;

}

Cuboid::Cuboid(glm::vec3 center, int width)
{
	transform.Position.x = center.x;
	transform.Position.y = center.y;
	transform.Position.z = center.z;

	float radius = width / 2;

	firstCorner = glm::vec3(center.x - radius, center.y - radius, center.z - radius);
	secondCorner = glm::vec3(center.x + radius, center.y + radius, center.z + radius);


}

Cuboid::Cuboid(glm::vec3 dimensions /*Values are converted to positive*/)
{
	float offsetX = abs(dimensions.x) / 2;
	float offsetY = abs(dimensions.y) / 2;
	float offsetZ = abs(dimensions.z) / 2;

	firstCorner = glm::vec3(-offsetX, -offsetY, -offsetZ);
	secondCorner = glm::vec3(offsetX, offsetY, offsetZ);
}

bool Cuboid::TestIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, OUT HitInfo& hit)
{
	float t_near = FLT_MIN;
	float t_far = FLT_MAX;

	for (int i = 0; i < 3; i++)
	{	
		//Verifica daca raza e || pe una dintre directii
		if (rayOrigin[i] == 0)
		{	
			//Verifica daca fiind paralela poate totusi intersecta Cuboidul
			if (rayOrigin[i] < std::min(firstCorner[i], secondCorner[i]) || rayOrigin[i] > std::max(firstCorner[i], secondCorner[i]))
			{
				return false;
			}
			
		}

		//Distantele pana la plane
		float t1 = (firstCorner[i] - rayOrigin[i]) / rayDir[i];
		float t2 = (secondCorner[i] - rayOrigin[i]) / rayDir[i];

		//Schimba in cazul in care colturile sunt invers
		if (t1 > t2)
		{
			float temp;
			temp = t1;
			t1 = t2;
			t2 = temp;
		}

		//Actualizeaza t_far si t_near
		if (t1 > t_near)
		{
			t_near = t1;
		}
		if (t2 < t_far)
		{
			t_far = t2;
		}

		//Raza se afla in spate
		if (t_far < 0)
		{
			return false;
		}
		//Raza rateaza
		if (t_near > t_far)
		{
			return false;
		}
	}

	
	//TODO CHECK RAY DIRECTION INVALID , or do it before
	//TODO get hit info

	return true;
}
