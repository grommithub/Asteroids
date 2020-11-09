#pragma once
#include "Shape2D.h"
class Circle : public Shape2D
{
public:
	float radius;


	Circle(float radius);

	// Inherited via Shape2D
	virtual std::vector<LineSegment> GetLinesToRender() override;

	// Inherited via Shape2D
	//virtual void Render() override;
};

