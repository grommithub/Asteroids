#include "Shape2D.h"

Shape2D::Shape2D() : center(&localCenter), localCenter(Vector2()), rotation(&localRotation), localRotation(0.0f)
{
}

void Shape2D::SetCenter(Vector2& v)
{
	center = &v;
}

void Shape2D::AddRotation(float f)
{
	*rotation += f;
}
