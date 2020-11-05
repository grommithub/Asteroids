#pragma once
#include "Vector2.h"
#include "Matrix.h"
#include <vector>
#include "LineSegment.h"

class Shape2D
{
public:
	Vector2* center;
	Vector2 localCenter;

	Shape2D();
	void SetCenter(Vector2& v);

	Vector2 GetCenter() { return *center; }

	float rotation;
	virtual std::vector<LineSegment> GetLinesToRender() = 0;

};

