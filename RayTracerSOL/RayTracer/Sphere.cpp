#include "Sphere.h"

bool Sphere::hit(const Ray &r, hit_record &rec)
{
	float X_d = r.direction.x;
	float X_o = r.origin.x;
	float X_c = center.x;

	float Y_d = r.direction.y;
	float Y_o = r.origin.y;
	float Y_c = center.y;

	float Z_d = r.direction.z;
	float Z_o = r.origin.z;
	float Z_c = center.z;

	float B = 2 * (X_d * (X_o - X_c) + Y_d * (Y_o - Y_c) + Z_d * (Z_o - Z_c));
	float C = glm::pow((X_o - X_c), 2) + glm::pow((Y_o - Y_c), 2) + glm::pow((Z_o - Z_c), 2) - glm::pow(radius, 2);

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

	rec.intersectPoint = glm::vec3(X_o + X_d * t0, Y_o + Y_d * t0, Z_o + Z_d * t0);
	rec.intersectNormal = glm::vec3((rec.intersectPoint.x - X_c) / radius, (rec.intersectPoint.y - Y_c) / radius, (rec.intersectPoint.z - Z_c) / radius);
	rec.t = t0;

	return true;

}
