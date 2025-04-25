#pragma once
#include "Hitable.h"

class Sphere : public Hitable {
	public:
		Vec3 center;
		float radious;
	
		Sphere() : center{ Vec3(0.0f, 0.0f, 0.0f) }, radious{0.0f} {};
		Sphere(Vec3 cen, float r) : center(cen), radious(r) {};
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

bool Sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	Vec3 oc = center - r.origin();
	float a = dot(r.direction(), r.direction());
	float b = -2.0f * dot(r.direction(), oc);
	float c = dot(oc, oc) - radious * radious;
	float discriminant = b * b - 4 * a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b * b - a * c)) / a; //positive root
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radious;
			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a; //negative root
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radious;
			return true;
		}
	}
	return false;
};