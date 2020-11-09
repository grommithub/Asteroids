#include "Circle.h"

Circle::Circle(float r) : radius(r)
{
}

std::vector<LineSegment> Circle::GetLinesToRender()
{
	int segments = 36;
	std::vector<LineSegment> lines;

	
		Vector2 last = GetPivotPoint(), current;
		for (int i = 0; i < 360; i+= 360/segments)
		{
			LineSegment l;
			For(j, 2)
			{
				l.points[j] = last;
				current = Vector2(GetPivotPoint().x + sin(i / 180.0f * PI) * radius, GetPivotPoint().y + cos(i / 180.0f * PI) * radius);
				last = current;
			}
			lines.push_back(l);

		}
		return lines;
}
