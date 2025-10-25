#pragma once
//#include "Hitable.h"
#include "Vec3.h"
#include "color.h"
#include "material.h"
class Camera {
	public:
		float aspect_ratio = 1.0f;
		int image_width = 100;
		int samples_per_pixel = 10;
		int max_depth = 10;

		float vfov = 90; //vertical view angle
		Vec3 lookfrom = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 lookat = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 vup = Vec3(0.0f, 1.0f, 0.0f);

		float defocus_angle = 0.0f;
		float focus_dist = 10.0f;

		void render(const Hitable& world) {
			initialize();

			std::ofstream ppm_file;
			ppm_file.open("generated_image.ppm");

			//ppm hello world
			ppm_file << "P3" << '\n'; //marcado como que la imagen es un pixmap donde los valores se guardan en ASCII, y no en binario.
			ppm_file << image_width << ' ' << image_height << '\n'; //ancho y largo de la imagen en pixeles. 
			ppm_file << 255 << '\n'; //marcado como que el valor mas grande de cada componente es 255.

			//ppm files are made by defining every value in a row before passing to the next one
			//thats why we define 
			float progress = 0.0f;
			for (int y = 0; y < image_height; y++) {
				for (int x = 0; x < image_width; x++) {
					color pixel_color(0.0f, 0.0f, 0.0f);
					for (int sample = 0; sample < samples_per_pixel; sample++) {
						ray r = get_ray(x, y);
						pixel_color += ray_color(r, max_depth, world);
					}
					Vec3 pixel_sample_result = pixel_samples_scale * pixel_color;
					write_color(ppm_file, pixel_sample_result);
					std::cout << "progress: " << (float(++progress) / float(image_width * image_height)) * 100.0f << "%" << '\n';
				}
			}
		}
	 
	private:
		int image_height;
		float pixel_samples_scale;
		Vec3 center;
		Vec3 pixel100_loc;
		Vec3 pixel_delta_u;
		Vec3 pixel_delta_v;
		Vec3 u, v, w;
		Vec3 defocus_disk_u;
		Vec3 defocus_disk_v;

		void initialize() { //initialize camera variables
			image_height = int(image_width / aspect_ratio);
			image_height = (image_height < 1) ? 1 : image_height;

			pixel_samples_scale = 1.0f / samples_per_pixel;

			center = lookfrom;

			float theta = degrees_to_radians(vfov);
			float h = std::tan(theta/2);
			float viewport_height = 2.0f * h * focus_dist;
			float viewport_width = viewport_height * (float(image_width)/image_height);

			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);

			Vec3 viewport_u = viewport_width * u;
			Vec3 viewport_v = viewport_height * -v; 

			pixel_delta_u = viewport_u / image_width;
			pixel_delta_v = viewport_v / image_height;

			Vec3 viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
			pixel100_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);

			float defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2.0f));
			defocus_disk_u = u * defocus_radius;
			defocus_disk_v = v * defocus_radius;

		}

		ray get_ray(int x, int y) const {
			Vec3 offset = sample_square();
			Vec3 pixel_sample = pixel100_loc + ((x + offset.x()) * pixel_delta_u) + ((y + (offset.y())) * pixel_delta_v);

			Vec3 ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
			Vec3 ray_direction = pixel_sample - ray_origin;

			return ray(ray_origin, ray_direction);
		}

		Vec3 sample_square() const {
			return Vec3(random_float() - 0.5f, random_float() - 0.5f, 0.0f);
		}

		Vec3 defocus_disk_sample() const {
			Vec3 p = random_in_unit_disk();
			return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
		}

		color ray_color(const ray& r, int depth, const Hitable& world) const {
			if (depth <= 0) { 
				// TODO for dielectrics, all pixels are hitting here, making them take this color. change depth and start testing when is this called for the other materials.
				//maybe since the point "traverses" the material, we get a lot of child rays inside the material?
				return color(1.0f, 0.0f, 0.0f);
			}

			hit_record rec;
			if (world.hit(r, interval(0.001f, infinity), rec)) {
				ray scattered;
				Vec3 attenuation;
				if (rec.mat->scatter(r, rec, attenuation, scattered)) {
					return attenuation * ray_color(scattered, depth - 1, world);
				}
				return color(0.0f, 0.0f, 0.0f);
			}
			Vec3 unit_direction = unit_vector(r.direction());
			float a = 0.5f * (unit_direction.y() + 1.0f);
			return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
		}
};