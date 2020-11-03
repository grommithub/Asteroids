#pragma once

#include<string>

struct Vector2
{
	float x, y;

	static Vector2 Up();
	static Vector2 Down();
	static Vector2 Left();
	static Vector2 Right();
	static Vector2 Zero();

	Vector2 operator + (const  Vector2& other) const;
	Vector2 operator - (const Vector2& other) const;
	Vector2 operator / (const float   divisor) const;
	Vector2 operator * (const Vector2& other) const;
	Vector2 operator * (const float factor) const;

	bool operator==(const Vector2& other);

	Vector2& operator =  (const Vector2& other);
	Vector2& operator += (const  Vector2& other);
	Vector2& operator -= (const Vector2& other);
	Vector2& operator /= (const float   divisor);
	Vector2& operator *= (const Vector2& other);
	Vector2& operator *= (const float factor);


	float SquareMagnitude() const;
	float Magnitude() const;
	void Normalize();
	void Round();
	Vector2 Unit();
	Vector2 Rounded();
	void Clamp(float magnitude);

	Vector2();
	Vector2(float x, float y);
	Vector2(int x, int y);
	std::string ToString();
};

