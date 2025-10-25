#include "rtweekend.h"

#include <fstream>

#include "Camera.h"
//#include "Hitable.h"
#include "Hitable_List.h"
//#include "float.h"
//#include "Vec3.h"
//#include "Color.h"
//#include "material.h"
#include "Sphere.h"
#include "Interval.h"
//#include "Ray.h"

color ray_color(const ray& r, const Hitable& world) {
	hit_record rec;
	if (world.hit(r, interval(0, infinity), rec)) { ;
		return 0.5f * (rec.normal + Vec3(1.0f, 1.0f, 1.0f));
	}
	Vec3 unit_direction = unit_vector(r.direction());
	float a = 0.5f * (unit_direction.y() + 1.0f); 
	return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a*color(0.5f, 0.7f, 1.0f);
}

int main() {
	Hitable_List world;

	auto ground_material = make_shared<Lambertian>(Vec3(0.5f, 0.5f, 0.5f));
	world.add(make_shared<Sphere>(Vec3(0.0f, -1000.0f, 0.0f), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = random_float();
			Vec3 center(a + 0.9f * random_float(), 0.2f, b + 0.9f * random_float());

			if ((center - Vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8f) {
					//diffuse
					Vec3 albedo = Vec3(random_float(0.0f, 1.0f), random_float(0.0f, 1.0f), random_float(0.0f, 1.0f)) * Vec3(random_float(0.0f, 1.0f), random_float(0.0f, 1.0f), random_float(0.0f, 1.0f));
					sphere_material = make_shared<Lambertian>(albedo);
					world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
				}
				else if (choose_mat < 0.95f) {
					//metal
					Vec3 albedo = Vec3(random_float(0.5f, 1.0f), random_float(0.5f, 1.0f), random_float(0.5f, 1.0f));
					float fuzz = random_float(0.0f, 0.5f);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
				}
				else {
					//glass
					sphere_material = make_shared<dielectric>(1.5f);
					world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5f);
	world.add(make_shared<Sphere>(Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));

	auto material2 = make_shared<Lambertian>(Vec3(0.4f, 0.2f, 0.1f));
	world.add(make_shared<Sphere>(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

	auto material3 = make_shared<metal>(color(0.7f, 0.6f, 0.5f), 0.0f);
	world.add(make_shared<Sphere>(Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));

	Camera cam;

	cam.aspect_ratio = 16.0f / 9.0f;
	cam.image_width = 1200;
	cam.samples_per_pixel = 50;
	cam.max_depth = 50;

	cam.vfov = 20;
	cam.lookfrom = Vec3(13.0f, 2.0f, 3.0f);
	cam.lookat = Vec3(0.0f, 0.0f, 0.0f);
	cam.vup = Vec3(0.0f, 1.0f, 0.0f);

	cam.defocus_angle = 0.6f;
	cam.focus_dist = 10.0f;

	cam.render(world);

	return 0;
}

int old_main() {

	int a;
	Hitable_List world;

	auto material_ground = make_shared<Lambertian>(Vec3(0.8f, 0.8f, 0.0f));
	auto material_center = make_shared<Lambertian>(Vec3(0.1f, 0.2f, 0.5f));
	auto material_left = make_shared<dielectric>(1.5f);
	//auto material_left = make_shared<metal>(Vec3(1.0f, 1.0f, 1.0f), 0.0f);
	auto material_bubble = make_shared<dielectric>(1.0f/1.5f);
	auto material_right = make_shared<metal>(Vec3(0.8f, 0.6f, 0.2f), 1.0f);

	world.add(make_shared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
	world.add(make_shared<Sphere>(Vec3(0.0f, 0.0f, -1.2f), 0.5f, material_center));
	world.add(make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, material_left));
	world.add(make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.4f, material_bubble));
	world.add(make_shared<Sphere>(Vec3(1.0f, 0.0f, -1.0f), 0.5f, material_right));

	Camera cam;
	cam.aspect_ratio = 16.0f / 9.0f;
	cam.image_width = 400.0f;
	cam.samples_per_pixel = 100.0f;
	cam.max_depth = 50;
	cam.vfov = 20;
	cam.lookfrom = Vec3(-2.0f, 2.0f, 1.0f);
	cam.lookat = Vec3(0.0f, 0.0f, -1.0f);
	cam.vup = Vec3(0.0f, 1.0f, 0.0f);

	cam.defocus_angle = 10.0f;
	cam.focus_dist = 3.4f;

	cam.render(world);

	return 0;
}