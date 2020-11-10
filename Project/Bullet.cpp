#include "Bullet.h"

Bullet::Bullet(float rotation, Vector2 position, bool particle) : speed(15.0f), maxDistance(1000.0f)
{
	if (particle) {
		maxDistance /= (8 + rand() % 4);
		speed /= 2.0f;

	}

	_position = position;
	LineSegment l = LineSegment(Vector2(0.0f, 3.0f), Vector2(0.0f, -3.0f));
	_lines.push_back(l);
	_rotation = rotation;

	Matrix m = Matrix::GetRotationMatrix(rotation);

	direction = m.GetTransformedVector(Vector2::Up() * speed);
	
}

void Bullet::Update()
{
	_position += direction;
	distance += speed;
}

bool Bullet::GetShouldDie()
{
	return distance >= maxDistance;
}

