#include "Bullet.h"

Bullet::Bullet(float rotation, Vector2 position) : speed(15.0f)
{
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
}

