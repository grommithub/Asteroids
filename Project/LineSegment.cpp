#include "LineSegment.h"

Vector2& LineSegment::Head()
{
	return points[0];
}

Vector2& LineSegment::Tail()
{
	return points[1];
}

float LineSegment::Length()
{
	return (points[0] - points[1]).Magnitude();
}
