#pragma once

#include "Renderer.h"
#include "Matrix.h"

class VectorShape
{
protected:
	float _rotation;
	Vector2 _scale;
	std::vector<LineSegment> _lines;
public:
	Vector2 _position;
	VectorShape(Vector2 position = Vector2());
	std::vector<LineSegment> GetLinesToRender();
	void SetPosition(Vector2 position);
	void SetPosition(float x, float y) { _position = Vector2(x, y); }
	void SetPositionX(float x) { _position.x = x; }
	void SetPositionY(float y) { _position.y = y; }
	void SetRotation(float r) { _rotation = r; }
	Vector2 GetPosition() { return _position; }
	float GetRotation() { return _rotation; }
	void AddRotation(float rd) { _rotation += rd; }
	void SetScale(Vector2 v) { _scale = v; }

	Vector2 GetLowestPoint();
	Vector2 GetHighestPoint();
	Vector2 GetLeftMostPoint();
	Vector2 GetRightMostPoint();
	float lowestPoint, highestPoint, leftMostPoint, rightMostPoint;

};

