#include "Vector2.h"


Vector2 Vector2::Up()
{
	return Vector2(0, -1);
}

Vector2 Vector2::Down()
{
	return Vector2(0, 1);
}

Vector2 Vector2::Left()
{
	return Vector2(-1, 0);
}

Vector2 Vector2::Right()
{
	return Vector2(1, 0);
}

Vector2 Vector2::Zero()
{
	return Vector2();
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator/(const float divisor) const
{
	return Vector2(x / divisor, y / divisor);
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator*(const float factor) const
{
	return Vector2(x * factor, y * factor);
}

Vector2& Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}

bool Vector2::operator==(const Vector2& other)
{
	return(x == other.x && y == other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2& Vector2::operator/=(const float divisor)
{
	x /= divisor;
	y /= divisor;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2& Vector2::operator*=(const float factor)
{
	x *= factor;
	y *= factor;

	return *this;
}

float Vector2::SquareMagnitude() const
{

	return (x * x) + (y * y);
}

float Vector2::Magnitude() const
{
	return sqrt(SquareMagnitude());
}

void Vector2::Normalize()
{
	float magnitude = Magnitude();
	if (magnitude == 0.0f) return;
	x /= magnitude;
	y /= magnitude;
}
/**
Rounds x and y to thier nearest respective integer values
*/
void Vector2::Round()
{
	x = (float)(int)(x + 0.5f);
	y = (float)(int)(y + 0.5f);
}

Vector2 Vector2::Unit()
{
	float magnitude = Magnitude();
	if (magnitude == 0.0f) return Zero();
	Vector2 p = Vector2(x / magnitude, y / magnitude);
	return Vector2(x / magnitude, y / magnitude);
}

Vector2 Vector2::Rounded()
{
	return Vector2((float)(int)x, (float)(int)y);
}

void Vector2::Clamp(float magnitude)
{
	if (SquareMagnitude() > (magnitude * magnitude))
	{
		Normalize();
		*this *= magnitude;
	}
}

Vector2::Vector2() : x(0.0f), y(0.0f)
{}

Vector2::Vector2(int x, int y) : x((float)x), y((float)y)
{}

Vector2::Vector2(float x, float y) : x(x), y(y)
{}

std::string Vector2::ToString()
{
	return '(' + std::to_string(x) + ',' + std::to_string(y) + ")\n";
}
