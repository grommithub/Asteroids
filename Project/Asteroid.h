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
	int GetPoints()
	{
		switch (size)
		{
		case BIG:
			return 100;
		case MEDIUM:
			return 75;
		case SMALL:
			return 50;
		default:
			return 0;
		}
	}
private:

	void SetLines();


};

