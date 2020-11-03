#include "VectorShape.h"

VectorShape::VectorShape(Vector2 position) : _rotation(0.0f), _scale(Vector2(1.0f, 1.0f)), _position(position)
{
}

std::vector<LineSegment> VectorShape::GetLinesToRender()
{
	std::vector<LineSegment> linesToRender(32);

	Matrix m = Matrix();

	
	m.SetScale(_scale);
	m.SetRotation(_rotation);
	m.SetOffset(_position);

	For(i, _lines.size())
	{
		LineSegment l;
		For(j, 2)
		{
			l.points[j] = m.GetTransformedVector(_lines[i].points[j]);
		}
		linesToRender.push_back(l);
	}
	return linesToRender;
}
