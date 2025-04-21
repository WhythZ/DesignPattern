#include "Vector2.h"
#include <cmath>

Vector2::Vector2(float x, float y): x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& vec) const
{
	return Vector2(x + vec.x, y + vec.y);
}

void Vector2::operator+=(const Vector2& vec)
{
	x += vec.x, y += vec.y;
}

Vector2 Vector2::operator-(const Vector2& vec) const
{
	return Vector2(x - vec.x, y - vec.y);
}

void Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x, y -= vec.y;
}

float Vector2::operator*(const Vector2& vec) const
{
	return x * vec.x + y * vec.y;
}

Vector2 Vector2::operator*(float val) const
{
	return Vector2(x * val, y * val);
}

void Vector2::operator*=(float val)
{
	x *= val, y *= val;
}

Vector2 Vector2::operator/(float val) const
{
	return Vector2(x / val, y / val);
}

void Vector2::operator/=(float val)
{
	x /= val, y /= val;
}

Vector2 Vector2::Normalize()
{
	float len = Length();

	if (len == 0)
		return Vector2(0, 0);

	return Vector2(x / len, y / len);
}

float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

bool Vector2::ApproxZero() const
{
	return Length() < 0.0001f;
}