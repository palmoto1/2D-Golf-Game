#ifndef VECTOR_H
#define VECTOR_H

#include <iostream> 

/*mathemaical vector*/

struct Vector
{
	float x = 0.0f;
	float y = 0.0f;

	Vector();
	Vector(float x, float y);


	friend Vector operator+(const Vector& left, const Vector& right);
	friend Vector operator-(const Vector& left, const Vector& right);
	friend Vector operator*(const Vector& left, const Vector& right);
	friend Vector operator/(const Vector& left, const Vector& right);

	Vector& operator+=(const Vector& other);
	Vector& operator-=(const Vector& other);
	Vector& operator*=(const Vector& other);
	Vector& operator/=(const Vector& other);

	Vector& zero();

	void normalize();

};

inline Vector operator*(const Vector& left, float right) {
	Vector temp(left);
	temp.x *= right;
	temp.y *= right;
	return temp;
}

inline Vector operator*(float left, const Vector& right) {
	return right * left;
}

inline Vector operator/(const Vector& left, float right) {
	Vector temp(left);
	temp.x /= right;
	temp.y /= right;
	return temp;
}

inline Vector operator/(float left, const Vector& right) {
	return right / left;
}
#endif

