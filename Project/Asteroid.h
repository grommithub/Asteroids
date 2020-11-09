#pragma once
#include "VectorShape.h"
#include "Circle.h"
#include <cstdlib>
class Asteroid : public VectorShape
{

public:
	enum Sizes
	{
		BIG,
		MEDIUM,
		SMALL,
		NOTHING
	};

	float radius;

	float speed, rotationSpeed;
	Vector2 direction;

	int minsegments, maxSegments;
	Asteroid(Vector2 position, Vector2 d, int size);
	Circle circle;
	int size;
	void Update();
private:

	void SetLines();


};

