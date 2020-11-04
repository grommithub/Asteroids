#pragma once
#include "Vector2.h"
#include "Matrix.h"
#include <vector>
#include "LineSegment.h"

class Shape2D
{
public:
	Vector2* center;
	float rotation;
	virtual std::vector<LineSegment> GetLinesToRender() = 0;

};

