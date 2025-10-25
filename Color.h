#pragma once
#include"Vec3.h"
#include "Interval.h"
using color = Vec3;
inline float linear_to_gamma(float linear_component) {
	if (linear_component > 0.0f) {
		return std::sqrt(linear_component);
	}
	return 0.0f;
}

void write_color(std::ostream& out, color& pixel_color) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	//translate 0 to 1 component values to the byte range 0 to 255
	static const interval intensity(0.0f, 0.999f);
	int rbyte = int(255.999 * intensity.clamp(r));
	int gbyte = int(255.999 * intensity.clamp(g));
	int bbyte = int(255.999 * intensity.clamp(b));

	//write out the pixel components
	out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ' << '\n';
}