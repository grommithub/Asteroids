#pragma once
#include "VectorShape.h"
#include "Rectangle.h"
#include <SDL_keycode.h>
#include "Shape2D.h"
class Player : public VectorShape
{
public:
	Player();
	Rect collisionBox;

	Vector2 velocity;
	float acceleration, retardation, steeringSpeed;

	void OnKeyDown(int key);
	void OnKeyUp(int key);

	bool left, right, up, shoot, canShoot;

	void Update();
	bool GetShoot();
};

