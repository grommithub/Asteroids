#pragma once

#include "Renderer.h"
#include "Matrix.h"

class VectorShape
{
protected:
	Vector2 _position;
	float _rotation;
	Vector2 _scale;
	std::vector<LineSegment> _lines;
public:
	VectorShape(Vector2 position = Vector2());
	std::vector<LineSegment> GetLinesToRender();
	void SetPosition(Vector2 position) { _position = position; }
	void SetPosition(float x, float y) { _position = Vector2(x, y); }
	void SetPositionX(float x) { _position.x = x; }
	void SetPositionY(float y) { _position.y = y; }
	void SetRotation(float r) { _rotation = r; }
	void SetScale(Vector2 v) { _scale = v; }
};

