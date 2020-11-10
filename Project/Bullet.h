#pragma once
#include "VectorShape.h"
#include "Rectangle.h"

class Bullet : public VectorShape
{
public:
	float speed;
	//Rect r;
	Bullet(float rotation, Vector2  position, bool particle);

	float maxDistance, distance;
	Vector2 direction;

	void Update();
	bool GetShouldDie();
};

