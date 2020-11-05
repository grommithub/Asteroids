#include "CollisionManager.h"

bool CollisionManager::CheckCollision(Vector2& v, Rect& r)
{
	Matrix m; //= Matrix::GetRotationMatrix(-r.rotation);
	m.SetOffset(r.GetCenter());

	v = m.GetTransformedVector(v);
	

	return(v.x >= r.center->x - r.half.x && v.x <= r.center->x + r.half.x && v.y >= r.center->y - r.half.y && v.y <= r.center->y + r.half.y);
}





bool CollisionManager::CheckCollision(Vector2& v, Circle& c)
{
	return (v - *c.center).SquareMagnitude() <= c.radius * c.radius;
}

bool CollisionManager::CheckCollision(Circle& c, Vector2& v)
{
	return CheckCollision(v,c);
}

bool CollisionManager::CheckCollision(Rect& r, Vector2& v)
{
	return CheckCollision(v, r);
}
