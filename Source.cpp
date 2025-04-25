#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Hitable_List.h"
#include "float.h"
#include "Camera.h"
#include <random>

//given a center of a sphere, the radious of a spehre, and a ray. calculate if the ray hits. i.e: there is a t for the ray that satifies the 
// sphere parametric equation
/*
float hit_sphere(const Vec3& center, float radious, const ray& r) {
	Vec3 oc = center - r.origin();
	float a = dot(r.direction(), r.direction());
	float b = -2.0f * dot(r.direction(), oc);
	float c = dot(oc, oc) - radious * radious;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return -1.0f;
	}
	else { //this enters if the ray hits
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}
}
Vec3 color(const ray& r) {
	float t = hit_sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f, r);

	//if  the ray hits. i.e there is a t that satisfies the sphere equation
	if ( t > 0.0f )  {
		//calculate the normal vector from that point. it is the point in the sphere hit by the ray minus the center of the sphere. we turn it into a 
		// unit vector
		//Vec3 N = unit_vector(r.point_at_parameter(t) - Vec3(0.0f, 0.0f, -1.0f));
		//return 0.5f * Vec3(N.x() + 1.0f, N.y() + 1.0f, N.z() + 1.0f);
		return Vec3(0.5f, 0.0f, 0.5f);
	}
	//if not, show the blend between white and blue we defined
	Vec3 unit_direction = unit_vector(r.direction());
	t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}
*/

Vec3 color(const ray& r, Hitable* world) {
	hit_record rec;
	if (world->hit(r, 0.0f,  FLT_MAX, rec)) { //if it hits anything in the world
		return 0.5f * Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1); //we calculate the normal
	}
	else {
		Vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
	}
}

int main() {
	
	//pruebas vec3
	Vec3 vec1 = *(new Vec3(25.0f, 15.0f, 2.0f));

	Vec3 lower_left_corner(-2.0f, -1.0f, -1.0f); //lower left corner for the portview we want
	Vec3 horizontal(4.0f, 0.0f, 0.0f); //movement on the x axis for the rays we generate
	Vec3 vertical(0.0f, 2.0f, 0.0f); //movement on the y axis for the rays we generate
	Vec3 origin(0.0f, 0.0f, 0.0f); //origin of our camera
	
	Hitable* list[2];
	list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
	list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f);
	Hitable* world = new Hitable_List(list, 2.0f);

	//crear un ppm de prueba
	std::ofstream ppm_file;
	ppm_file.open("generated_image.ppm");

	//ppm hello world
	ppm_file << "P3" << '\n'; //marcado como que la imagen es un pixmap donde los valores se guardan en ASCII, y no en binario.
	ppm_file << "200 100" << '\n'; //ancho y largo de la imagen en pixeles. 
	ppm_file << 255 << '\n'; //marcado como que el valor mas grande de cada componente es 255.

	//200 columns, 100 rows
	int nx = 200; //width
	int ny = 100; //height
	int ns = 100;

	Camera cam;

	//random distribution
	std::uniform_real_distribution<float> dis(0.0f, 1.0f); //random number between 

	//ppm files are made by defining every value in a row before passing to the next one
	//thats why we define 
	for (int y = ny - 1; y >= 0; --y) {
		for (int x = 0; x < nx; ++x) {
			Vec3 col(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < ns; ++s) {
				float factor_r = float(x + dis()) / float(nx);
				float factor_g = float(y + dis()) / float(ny);
			
				ray r = cam.get_ray(factor_r, factor_g);
				Vec3 p = r.point_at_parameter(2.0f);
				col += color(r, world);
			}
			col /= float(ns);
			ppm_file << int(255.0f * col[0]) << "	" << int(255.0f * col[1]) << "	" << int(255.0f * col[2]) << "\n";
		}
	}

	ppm_file.close();

	std::cout << "imagen generada";
	return 0;
}