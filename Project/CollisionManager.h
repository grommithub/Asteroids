#pragma once

#include "Rectangle.h"
#include "Matrix.h"
#include "Circle.h"
#include "MathsExtensions.h"

struct CollisionManager
{
	static bool CheckCollision(Vector2 v, Rect r);
	static bool CheckCollision(Rect r, Vector2 v);

	static bool CheckCollision(Vector2 v, Circle c);
	static bool CheckCollision(Circle r, Vector2 v);

	static bool CheckCollision(Circle c, Circle c2);
	
	//static bool CheckCollision(Rect r, Circle c);
};

