#include "Vector2.h"
#include <cmath>

Vector2::Vector2(float _x, float _y): x(_x), y(_y) {}

Vector2 Vector2::operator+(const Vector2& _vec) const
{
	return Vector2(x + _vec.x, y + _vec.y);
}

void Vector2::operator+=(const Vector2& _vec)
{
	x += _vec.x, y += _vec.y;
}

Vector2 Vector2::operator-(const Vector2& _vec) const
{
	return Vector2(x - _vec.x, y - _vec.y);
}

void Vector2::operator-=(const Vector2& _vec)
{
	x -= _vec.x, y -= _vec.y;
}

float Vector2::operator*(const Vector2& _vec) const
{
	return x * _vec.x + y * _vec.y;
}

Vector2 Vector2::operator*(float _val) const
{
	return Vector2(x * _val, y * _val);
}

void Vector2::operator*=(float _val)
{
	x *= _val, y *= _val;
}

Vector2 Vector2::operator/(float _val) const
{
	return Vector2(x / _val, y / _val);
}

void Vector2::operator/=(float _val)
{
	x /= _val, y /= _val;
}

Vector2 Vector2::Normalize()
{
	float _len = Length();

	if (_len == 0)
		return Vector2(0, 0);

	return Vector2(x / _len, y / _len);
}

float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

bool Vector2::ApproxZero() const
{
	return Length() < 0.0001f;
}