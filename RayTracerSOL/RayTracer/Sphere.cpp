#include "Sphere.h"
#include "..\\glm\gtx\normalize_dot.hpp"

bool Sphere::hit(const Ray &r, hit_record &rec)
{
	float X_d = r.direction.x; //directia razei
	float X_o = r.origin.x; // originea razei
	float X_c = center.x; // centrul sferei

	float Y_d = r.direction.y;
	float Y_o = r.origin.y;
	float Y_c = center.y;

	float Z_d = r.direction.z;
	float Z_o = r.origin.z;
	float Z_c = center.z;

	float difXoc = X_o - X_c;
	float difYoc = Y_o - Y_c;
	float difZoc = Z_o - Z_c;

	glm::vec3 OC = r.origin - center;
	float B = 2 * glm::dot(OC, r.direction);
	float C = glm::dot(OC, OC) - radius*radius;

	 //B = 2 * (X_d * (difXoc) + Y_d * (difYoc) + Z_d * (difZoc));
	 //C = glm::pow((difXoc), 2) + glm::pow((difYoc), 2) + glm::pow((difZoc), 2) - glm::pow(radius, 2);

	

	float discriminant = glm::pow(B, 2) - 4 * C;
	
	float t0 = (-B - glm::sqrt(discriminant)) / 2;
	if (t0 < 0)
	{
		rec.intersectPoint = glm::vec3(0.f, 0.f, 0.f);
		rec.intersectNormal = glm::vec3(0.f,0.f,0.f);
		return false;
	}
	float t1 = (-B + glm::sqrt(discriminant)) / 2;

	if (t1 > 0)
	{
		t0 = glm::min(t0, t1);
	}

	//Inregistrare valori
	rec.intersectPoint = r.ray_at_point(t0); 
	rec.intersectNormal = (rec.intersectPoint - center) / radius;
	//rec.intersectNormal = glm::vec3((rec.intersectPoint.x - X_c) / radius, (rec.intersectPoint.y - Y_c) / radius, (rec.intersectPoint.z - Z_c) / radius);
	rec.t = t0;

	return true;

}
