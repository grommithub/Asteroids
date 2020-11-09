#pragma once
#include "VectorShape.h"
#include "Rectangle.h"

class Bullet : public VectorShape
{
public:
	float speed;
	//Rect r;
	Bullet(float rotation, Vector2  position);
	Vector2 direction;

	void Update();
};

