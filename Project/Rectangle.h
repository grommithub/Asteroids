#pragma once
#include "Shape2D.h"
#include <vector>
#include "LineSegment.h"

class Rect : public Shape2D
{
public:
	enum  Alignment
	{
		TOPLEFT,
		TOPMID,
		TOPRIGHT,
		MIDDLELEFT,
		MIDDLE,
		BOTTOMLEFT,
		BOTTOMMID, 
		BOTTOMRIGHT
	};

	Alignment alignment;

	Vector2 half;

	void SetWidth(float w);
	void SetHeight(float h);
	Rect(float w, float h);
	float GetHeight();
	float GetWidth();

	Vector2 GetOffsetByAlignment();

	Vector2 GetTopLeft();
	//Vector2 GetBottomLeft();
	//Vector2 GetTopRight();
	//Vector2 GetBottomRight();

	virtual std::vector<LineSegment> GetLinesToRender() override;
};

