//HEADER PRINCIPAL CON DEFINICIONES DE CONSTANTES, LLAMADOS A OTROS HEADERS, Y FUNCIONES AUXILIARES
#pragma once
#include <cmath>
#include <iostream>
#include <memory>
#include <cstdlib>

//C++ std usings
using std::make_shared;
using std::shared_ptr;

//Constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

//Utility Functions
inline float degrees_to_radians(float degrees) {
	return degrees * pi / 180.0f;
}

//returns a random real in [0, 1)
inline float random_float() {
	return std::rand() / (RAND_MAX + 1.0f);
}

//return a random real in [min, max)
inline float random_float(float min, float max) {
	return min + (max - min) * random_float();
}

//Common headers
//#include "Vec3.h"
//#include "Color.h"
//#include "Interval.h"
//#include "Ray.h"