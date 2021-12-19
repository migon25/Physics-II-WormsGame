#include "Vector2.h"
#include "Math.h"

#include <iostream>

Vector2::Vector2()
{
}

Vector2::Vector2(double _x, double _y)
{
	x = _x;
	y = _y;
}


Vector2::~Vector2()
{
}

void Vector2::Normalize()
{
	double m = Magnitude();

	if (m != 0) {
		x /= m;
		y /= m;
	}
}

bool Vector2::IsNormalized()
{
	return Magnitude() == 1 ? true : false;
}

double Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

double Dot(const Vector2 & v1, const Vector2 & v2)
{
	double product = 0.0;

	product += v1.x * v2.x;
	product += v1.y * v2.y;

	return product;
}

void operator*=(Vector2 & v1, double s)
{
	v1.x *= s;
	v1.y *= s;
}

void operator+=(Vector2 & v1, const Vector2 & v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
}

Vector2 operator+(const Vector2 & v1, const Vector2 & v2)
{
	Vector2 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;

	return v;
}

Vector2 operator-(const Vector2 & v1, const Vector2 & v2)
{
	Vector2 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;

	return v;
}

Vector2 operator+(const Vector2 & v, double s)
{
	Vector2 vec;

	vec.x = v.x + s;
	vec.y = v.y + s;

	return vec;
}

Vector2 operator*(double s, const Vector2 & v)
{
	Vector2 vec;

	vec.x = v.x * s;
	vec.y = v.y * s;

	return vec;
}

Vector2 operator*(const Vector2 & v, double s)
{
	Vector2 vec;

	vec.x = v.x * s;
	vec.y = v.y * s;

	return vec;
}

Vector2 operator/(const Vector2 & v, double s)
{
	Vector2 vec;

	vec.x = v.x / s;
	vec.y = v.y / s;

	return vec;
}
