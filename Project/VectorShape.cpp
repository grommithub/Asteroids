#include "VectorShape.h"
#include <algorithm>

VectorShape::VectorShape(Vector2 position) : _rotation(0.0f), _scale(Vector2(1.0f, 1.0f)), _position(position), highestPoint(0.0f), lowestPoint(0.0f), leftMostPoint(0.0f), rightMostPoint(0.0f)
{
}

std::vector<LineSegment> VectorShape::GetLinesToRender()
{
	std::vector<LineSegment> linesToRender(32);

	Matrix m = Matrix();
	float hi = 100000.0f, low = -100000.0f, left = 100000.0f, right = -100000.0f;
	
	m.SetScale(_scale);
	m.SetRotation(_rotation);
	m.SetOffset(_position);

	For(i, _lines.size())
	{
		LineSegment l;
		For(j, 2)
		{
			l.points[j] = m.GetTransformedVector(_lines[i].points[j]);

			hi = std::min(hi, l.points[j].y);
			right = std::max(right, l.points[j].x);
			low = std::max(low, l.points[j].y);
			left = std::min(left, l.points[j].x);
		}
		linesToRender.push_back(l);
	}

	leftMostPoint = left;
	rightMostPoint = right;
	highestPoint = hi;
	lowestPoint = low;

	return linesToRender;
}

void VectorShape::SetPosition(Vector2 position)
{
	_position = position; 
}

Vector2 VectorShape::GetLowestPoint()
{
	return Vector2();
}

Vector2 VectorShape::GetHighestPoint()
{
	return Vector2();
}

Vector2 VectorShape::GetLeftMostPoint()
{
	return Vector2();
}

Vector2 VectorShape::GetRightMostPoint()
{
	return Vector2();
}
