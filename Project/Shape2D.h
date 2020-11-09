#pragma once
#include "Vector2.h"
#include "Matrix.h"
#include <vector>
#include "LineSegment.h"

struct Shape2D
{
	Vector2* center;
	Vector2 localCenter;

	float* rotation;
	float localRotation;

	Shape2D();
	void SetCenter(Vector2& v);



	Vector2 GetPivotPoint() { return *center; }
	float GetRotation() { return *rotation; }
	void SetRotation(float f) { *rotation = f; }
	void AddRotation(float f);

	void SetRotationReference(float& r) { rotation = &r; }

	virtual std::vector<LineSegment> GetLinesToRender() = 0;

};

