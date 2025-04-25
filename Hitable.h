#pragma once
#include "Ray.h"

struct hit_record {
	float t; //the t that made the ray hit the object 
	Vec3 p; //point where the ray hit the object, also a point in the object
	Vec3 normal; //normal of the point where the ray hit the object
};

class Hitable {
	public:
		virtual bool hit(const ray& r, float t_min, float  t_max, hit_record& rec) const = 0;
};