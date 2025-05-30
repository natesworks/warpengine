#pragma once

#include <math.h>

class Vector2
{
public:
	float x;
	float y;
	Vector2(float x, float y)
		: x(x)
		, y(y) { };
	Vector2()
		: x(0)
		, y(0) { };

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 operator-(const float num) const
	{
		return Vector2(x - num, y - num);
	}
	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator+(const float num) const
	{
		return Vector2(x + num, y + num);
	}
	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& operator+=(const float num)
	{
		x += num;
		y += num;
		return *this;
	}
	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2& operator-=(const float num)
	{
		x -= num;
		y -= num;
		return *this;
	}
	Vector2& operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	Vector2& operator*=(const float num)
	{
		x *= num;
		y *= num;
		return *this;
	}
	Vector2& operator/=(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vector2& operator/=(const float num)
	{
		x /= num;
		y /= num;
		return *this;
	}
	Vector2 operator*(const Vector2 other) const
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2 operator*(const float num) const
	{
		return Vector2(x * num, y * num);
	}
	Vector2 operator/(const Vector2 other) const
	{
		return Vector2(x / other.x, y / other.y);
	}
	Vector2 operator/(const float num) const
	{
		return Vector2(x / num, y / num);
	}
	bool operator==(const Vector2 other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator==(const float num) const
	{
		return x == num && y == num;
	}
	Vector2 normalised()
	{
		float length = sqrt(x * x + y * y);
		if (length == 0)
			return Vector2(0, 0);
		return Vector2(x / length, y / length);
	}
};
