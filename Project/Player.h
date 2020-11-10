#pragma once
#include "VectorShape.h"
#include "Rectangle.h"
#include <SDL_keycode.h>
#include "Shape2D.h"
#include "Circle.h"
class Player : public VectorShape
{
public:
	Player();
	Circle collision;

	LineSegment thrustLines[2];

	Vector2 fireEnd;

	Vector2 velocity;
	float acceleration, retardation, steeringSpeed, flameLength, flameLengthMax;

	void OnKeyDown(int key);
	void OnKeyUp(int key);

	bool left, right, up, shoot, canShoot;

	void Update();
	bool GetShoot();
	virtual std::vector<LineSegment> GetLinesToRender() override;
};

