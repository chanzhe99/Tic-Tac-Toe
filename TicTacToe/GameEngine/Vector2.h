#pragma once
#include <math.h>

class Vector2
{
public:
	float X, Y;

	Vector2()
	{
		X = 0;
		Y = 0;
	}

	Vector2(float XValue, float YValue)
	{
		X = XValue;
		Y = YValue;
	}

	Vector2 operator+(Vector2 OtherVector) { return Vector2(X + OtherVector.X, Y + OtherVector.Y); }
	Vector2 operator-(Vector2 OtherVector) { return Vector2(X - OtherVector.X, Y - OtherVector.Y); }
	Vector2 operator*(float OtherValue) { return Vector2(X * OtherValue, Y * OtherValue); }
	Vector2 operator/(float OtherValue) { return Vector2(X / OtherValue, Y / OtherValue); }
};