#pragma once
//#ifndef RAYH
//#define RAYH
#include "Vec3.h"

//un rayo se puede definir con la funcion p(t) = A + t*B
//A siendo el origen del rayo. 
//B siendo la direccion
//t siendo un real para marcar puntos diferentes a lo largo del rayo. (muy parecido a la pendiente en una recta?)
//P siendo puntos sobre ese rayo. 
//t puede ser positivo o negativo, permitiendo moverte entre varios puntos de la recta. 
//un t negativo son puntos atras de A, mientras que positivos son puntos adelante de A.
//cada parte de esto es una MITAD del rayo, llamado half-line. 

class ray {
	public:
		ray() {};

		ray(const Vec3& a, const Vec3& b) { A = a; B = b; }
		Vec3 origin() const { return A; }
		Vec3 direction() const { return B; }
		Vec3 point_at_parameter(float t) const { return A + t * B; }
	private:
		Vec3 A;
		Vec3 B;
};
//#endif
