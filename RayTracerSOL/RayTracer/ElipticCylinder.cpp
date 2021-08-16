#include "ElipticCylinder.h"

ElipticCylinder::ElipticCylinder(float radius,float minY,float maxY)
{	
	this->minY = minY;
	this->maxY = maxY;
	elipticX = radius;
}

bool ElipticCylinder::TestIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, OUT HitInfo& hit)
{	

	//TODO register intersection points in a vector instead of true and false
  float a = rayDir.x * rayDir.x + rayDir.z * rayDir.z;

  if (a < 0.0001)
  {
	  return false;
  }

  float b = 2 * rayOrigin.x * rayDir.x + 2 * rayOrigin.z * rayDir.z;
  float c = rayOrigin.x * rayOrigin.x + rayOrigin.z * rayOrigin.z - 1;

  float disc = b*b - 4 * a * c;

  if (disc < 0)
  {
	  return false;
  }

  float t0 = (-b - sqrt(disc)) / (2 * a);
  float t1 = (-b + sqrt(disc)) / (2 * a);


  float y0 = rayOrigin.y + t0 * rayDir.y;
  if (minY < y0 || y0 < maxY)
  {
	  return true;
  }
  float y1 = rayOrigin.y + t0 * rayDir.y;

  if (minY < y1 || y1 < maxY)
  {
	return true;
  }


  return true;
  
}

glm::vec3 ElipticCylinder::GetNormal(glm::vec3 hitPoint)
{
	return glm::vec3(hitPoint.x, 0, hitPoint.z);
}
