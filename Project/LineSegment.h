#pragma once
#include "Vector2.h"



struct LineSegment
{
	Vector2& Head();
	Vector2& Tail();

	Vector2 points[2];
	float Length();
};

