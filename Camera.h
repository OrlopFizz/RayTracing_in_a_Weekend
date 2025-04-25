#pragma once
#include "Ray.h"
class Camera {
	public:
		Vec3 origin;
		Vec3 lower_left_corner;
		Vec3 horizontal;
		Vec3 vertical;

		Camera() : lower_left_corner{ -2.0f,-1.0f, -1.0f }, horizontal{ 4.0f, 0.0f, 0.0f }, vertical{ 0.0f, 2.0f, 0.0f }, origin{0.0f, 0.0f, 0.0f} {};
		ray get_ray(float u, float v) {
			return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
		}
};