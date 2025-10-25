#pragma once
#include "Hitable.h"

class Sphere : public Hitable {
	public:
		Vec3 center;
		float radious;
		shared_ptr<material> mat;
	
		Sphere() : center{ Vec3(0.0f, 0.0f, 0.0f) }, radious{0.0f} {};
		Sphere(const Vec3& cen, float r, shared_ptr<material> mat) : center(cen), radious(std::fmax(0.0f, r)), mat(mat) {};

		bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
			Vec3 oc = center - r.origin();
			float a = r.direction().squared_length();
			float h = dot(r.direction(), oc);
			float c = oc.squared_length() - radious * radious;
			float discriminant = h * h - a * c;
			if (discriminant < 0) {
				return false;
			}
			float sqrtd = std::sqrt(discriminant);
			float root = (h - sqrtd) / a;
			
			if (!ray_t.surrounds(root)) { //si la raiz no esta dentro del rango
				root = (h + sqrtd) / a; //calcular la otra raiz
				if (!ray_t.surrounds(root)) //si tampoco esta dentro del rango
					return false; //no hay raiz dentro del rango. no hay colision
			}
			
			rec.t = root;
			rec.p = r.point_at_parameter(rec.t);
			//Vec3 outward_normal = unit_vector((rec.p - center)/radious);
			Vec3 outward_normal = (rec.p - center) / radious;
			rec.set_face_normal(r, outward_normal);
			rec.mat = mat;

			return true;
		};
};