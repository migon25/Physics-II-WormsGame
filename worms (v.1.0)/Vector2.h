#pragma once

class Quaternion;

class Vector2
{
public:
	Vector2();
	Vector2(double _x, double _y);
	~Vector2();

	double x, y;

	void Normalize();

	bool IsNormalized();

	double Magnitude();
};

double Dot(const Vector2& v1, const Vector2& v2);

void operator*=(Vector2& v1, double s);

Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);

Vector2 operator+(const Vector2& v, double s);
Vector2 operator*(double s, const Vector2& v);
Vector2 operator*(const Vector2& v, double s);
Vector2 operator/(const Vector2& v, double s);