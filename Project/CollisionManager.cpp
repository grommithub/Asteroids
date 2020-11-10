#include "CollisionManager.h"

bool CollisionManager::CheckCollision(Vector2 v, Rect r)
{
	/*
		This shit doesn't work unless the pivot's in the center and I'm not really bothered to fix it right now
	*/


	v = MathsExtensions::RotatedPoint(v, r.GetUnRotatedCenter(), -r.GetRotation());
	return(v.x >= r.GetUnRotatedCenter().x - r.half.x && v.x <= r.GetUnRotatedCenter().x + r.half.x && v.y >= r.GetUnRotatedCenter().y - r.half.y && v.y <= r.GetUnRotatedCenter().y + r.half.y);
}





bool CollisionManager::CheckCollision(Vector2 v, Circle c)
{
	return (v - *c.center).SquareMagnitude() <= c.radius * c.radius;
}

bool CollisionManager::CheckCollision(Circle c, Vector2 v)
{
	return CheckCollision(v,c);
}

bool CollisionManager::CheckCollision(Circle c, Circle c2)
{
	return (c.GetPivotPoint() - c2.GetPivotPoint()).SquareMagnitude() < (c.radius + c.radius) * (c.radius + c.radius);
}

//bool CollisionManager::CheckCollision(Rect r, Circle c)
//{
//	auto v = c.GetPivotPoint();
//	c.SetCenter(v);
//
//	v = MathsExtensions::RotatedPoint(v, r.GetUnRotatedCenter(), -r.GetRotation());
//
//	if (CheckCollision(v, r)) return true;
//	Vector2 dist;
//
//	if()
//}

bool CollisionManager::CheckCollision(Rect r, Vector2 v)
{
	return CheckCollision(v, r);
}
