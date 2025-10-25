#pragma once

#include "Ray.h"
//#include "Interval.h"

class material;
class interval;
class hit_record {
	public:
		float t; //the t that made the ray hit the object 
		Vec3 p; //point where the ray hit the object, also a point in the object
		Vec3 circle_center;
		Vec3 normal; //normal of the point where the ray hit the object
		bool front_face;
		shared_ptr<material> mat;
		
		void set_face_normal(const ray& r, const Vec3& outward_normal) {
			//set the record normal vector
			front_face = dot(r.direction(), outward_normal) < 0; //we get the dot product between the normal, and the direction of the ray, if its negative, the vectors are opposite
			normal = front_face ? outward_normal : -outward_normal;
		}
};

class Hitable {
	public:
		virtual ~Hitable() = default;

		virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};