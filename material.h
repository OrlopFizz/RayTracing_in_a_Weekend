#pragma once
#include "Hitable.h"
class material {
public:
	virtual ~material() = default;

	virtual bool scatter(const ray& r_in, const hit_record& rec, Vec3& attenuation, ray& scattered) const {
		return false;
	}
};

class Lambertian : public material {
	private:
		Vec3 albedo;

	public:
		Lambertian(const Vec3& albedo) : albedo(albedo) {};

		bool scatter(const ray& r_in, const hit_record& rec, Vec3& attenuation, ray& scattered) const override {
			auto scatter_direction = rec.normal + random_unit_vector();

			if (scatter_direction.near_zero()) {
				scatter_direction = rec.normal;
			}

			scattered = ray(rec.p, scatter_direction);
			attenuation = albedo;
			return true;
		}
};

class metal : public material {
	private:
		Vec3 albedo;
		float fuzz;
	
	public:
		metal(const Vec3& albedo, const float fuzz) : albedo(albedo), fuzz{fuzz < 1 ? fuzz : 1} {};

		bool scatter(const ray& r_in, const hit_record& rec, Vec3& attenuation, ray& scattered) const override {
			Vec3 reflected = reflect(r_in.direction(), rec.normal);
			reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
			scattered = ray(rec.p, reflected);
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		}
};

class dielectric : public material {
	private:
		float refraction_index;

		static float reflectance(float cosine, float refraction_index) {
			auto r0 = (1 - refraction_index) / (1 + refraction_index);
			r0 = r0 * r0;
			return r0 + (1 - r0) * std::pow((1 - cosine), 5);
		}

	public:
		dielectric(float refraction_index) : refraction_index(refraction_index) {};

		bool scatter(const ray& r_in, const hit_record& rec, Vec3& attenuation, ray& scattered) const override {
			attenuation = Vec3(1.0f, 1.0f, 1.0f);
			float ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
			Vec3 unit_direction = unit_vector(r_in.direction());

			float cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0f);
			float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);
			Vec3 direction;
			if (ri * sin_theta > 1.0f || reflectance(cos_theta, ri) > random_float()) { // the angle between the surface and the ray is too small, so it starts reflecting
				direction = reflect(unit_direction, rec.normal);
			}
			else {
				direction = refract(unit_direction, rec.normal, ri);
			}

			scattered = ray(rec.p, direction);
			return true;
		}
};