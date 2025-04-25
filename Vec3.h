//es util tener una clase de vector para hacer el manejo de estos.
//este siendo un archivo para declarar las funciones, variables, templates, constructs etc
//que necesita nuestra clases. Aqui pueden tener ciertas definiciones aca, como cosas inline
//o constructores pequeños.
//pero en general lo mejor es aca solo poner definiciones.
#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
class Vec3
{
	//constructor
	public:
		//array para representar el vector.
		float e[3];
		Vec3() {
			e[0] = 0.0f;
			e[1] = 0.0f;
			e[2] = 0.0f;
		}
		
		Vec3(float a, float b, float c) {
			e[0] = a;
			e[1] = b;
			e[2] = c;
		}
		inline float x() const { return e[0]; } //una funcion marcada como const es de solo lectura, no se puede cambiar el valor retornado
		inline float y() const { return e[1]; }
		inline float z() const { return e[2]; }
		inline float r() const { return e[0]; }
		inline float g() const { return e[1]; }
		inline float b() const { return e[2]; }

		//declaracion y definicion de funciones de acceso.
		inline Vec3& operator+() { //operador de acceso normal al objeto 
			return *this; 
		} 
		inline Vec3 operator-() const { //operador de menos, devuelve la inversa del vector.
			return Vec3(-e[0], -e[1], -e[2]); 
		}
		inline float operator[] (int i) const { //operador de indexacion, solo devuelve el valor
			return e[i]; 
		}
		inline float& operator[] (int i) { //operador de indexacion, devuelve un pointer para cambiar el valor. 
			return e[i]; 
		}
		
		//definicion de operaciones entre vectores y flotantes
		inline Vec3 operator/(float t) { return Vec3(e[0] / t, e[1] / t, e[2] / t); }
		inline Vec3 operator*(float t) { return Vec3(e[0] * t, e[1] * t, e[2] * t); };

		//declaracion de funciones de operaciones entre vectores
		inline Vec3& operator+=(const Vec3 &v2); //operador =+, recibe la REFERENCIA (&v2) a un Vec3, esto es una variable que guarda la direccion en memoria de un objeto, pero su referencia no se puede cambiar a otro objeto. 
		inline Vec3& operator-=(const Vec3 &v2); 
		inline Vec3& operator*=(const Vec3 &v2);
		inline Vec3& operator/=(const Vec3 &v2);
		inline Vec3& operator*=(const float t); //operador de multiplicacion escalar. todos los valores multiplicarlos por t.
		inline Vec3& operator/=( const float t); //operador de division escalar. todos los valores dividirlos por t.

		//declaracion y definicion de varias funciones para largo(magnitud) y normalizacion del vector. 
		inline float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
		inline float squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
		inline void make_unit_vector();

};

//declaracion y definicion de varios operadores
//operador de suma entre vectores
inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2){
	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2){
	return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(float lhs, Vec3 rhs) {
	return Vec3(rhs[0] * lhs, rhs[1] * lhs, rhs[2] * lhs);
}

//declaracion y definicion de funciones de operaciones geometricas.
inline float dot(const Vec3 &v1, const Vec3 &v2) {
	return  v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v1.e[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
	return Vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
				-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
				(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
	}

inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

inline Vec3& Vec3::operator+=(const Vec3& v2) {
	e[0] += v2.x();
	e[1] += v2.y();
	e[2] += v2.z();
	return *(this);
}

inline Vec3& Vec3::operator/= (const Vec3& v2) {
	e[0] /= v2.x();
	e[1] /= v2.y();
	e[2] /= v2.z();
	return *(this);
}

inline Vec3& Vec3::operator/= (const float t) {
	e[0] += t;
	e[1] += t;
	e[2] += t;
	return *(this);
}