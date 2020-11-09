#include "Asteroid.h"


Asteroid::Asteroid(Vector2 position, Vector2 d, int s) : radius(0.0f), circle(0.0), minsegments(6), maxSegments(10), speed(1.0f), rotationSpeed(rand() % (100 - 50) * .1f)
{
	size = s;
	switch (s)
	{
	case Asteroid::BIG:
		radius = 50.0f;
		break;
	case Asteroid::MEDIUM:
		radius = 30.0f;
		break;
	case Asteroid::SMALL:
		radius = 20.0f;
		break;
	default:
		break;
	}

	direction = d;

	circle.radius = radius;

	_position = position;
	circle.SetCenter(_position);
	_scale = Vector2(1.0f, 1.0f);

	SetLines();
}

void Asteroid::Update()
{
	_position += direction * speed;
	_rotation += rotationSpeed;
}

void Asteroid::SetLines()
{
	int segments = rand() % (maxSegments - minsegments) + minsegments;



	Vector2 last, current;
	for (int i = 0; i < 360; i += 360 / segments)
	{
		LineSegment l;
		For(j, 2)
		{
			l.points[j] = last;
			current = Vector2(sin(i / 180.0f * PI) * radius, cos(i / 180.0f * PI) * radius);
			last = current;
		}
		_lines.push_back(l);

	}

	LineSegment l = LineSegment(_lines[0].points[0], _lines[_lines.size() - 1].points[1]);

	_lines.push_back(l);

}
