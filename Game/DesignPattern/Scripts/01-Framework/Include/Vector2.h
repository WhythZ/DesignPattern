#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	float x = 0;
	float y = 0;

public:
	Vector2() = default;
	Vector2(float x, float y);
	~Vector2() = default;
	
	Vector2 operator+(const Vector2&) const;
	void operator+=(const Vector2&);
	Vector2 operator-(const Vector2&) const;
	void operator-=(const Vector2&);
	float operator*(const Vector2&) const;
	Vector2 operator*(float) const;
	void operator*=(float);
	Vector2 operator/(float) const;
	void operator/=(float);
	
	Vector2 Normalize();

	float Length() const;
	bool ApproxZero() const;
};

#endif
