#include "MathsExtensions.h"

Vector2 MathsExtensions::RotatedPoint(Vector2 point, Vector2 pivot, float degrees)
{
	//https://stackoverflow.com/a/2259502

	//sin and cos use radians, apparently
	//would have saved a lot of time if I knew this beforehand

	float s = sin(degrees / 180 * PI); //converting to radians
	float c = cos(degrees / 180 * PI);

	point = point - pivot;

	// rotate point
	float newX = point.x * c - point.y * s;
	float newY = point.x * s + point.y * c;

	// translate point back:

	point.x = newX + pivot.x;
	point.y = newY + pivot.y;
	return point;
}
