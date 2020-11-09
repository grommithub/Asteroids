#include "Rectangle.h"

Vector2 Rect::GetUnRotatedCenter()
{
	return GetPivotPoint() + GetOffsetByAlignment();
}

void Rect::SetWidth(float w)
{
	half.x = w / 2;
}

void Rect::SetHeight(float h)
{
	half.y = h / 2;
}

Rect::Rect(float w, float h) : alignment(Alignment::MIDDLE)
{
	half.x = w;
	half.y = h;
	half /= 2;
}

float Rect::GetHeight()
{
	return half.y * 2;
}

float Rect::GetWidth()
{
	return half.x * 2;
}

Vector2 Rect::GetOffsetByAlignment()
{
	switch (alignment)
	{
	case Rect::TOPLEFT:
		return Vector2(-half.x, -half.y);
		break;
	case Rect::TOPMID:
		return Vector2(0.0f, -half.y);
		break;
	case Rect::TOPRIGHT:
		return Vector2(half.x, -half.y);
		break;
	case Rect::MIDDLELEFT:
		return Vector2(-half.x, 0.0f);
		break;
	case Rect::MIDDLE:
		return Vector2(0.0f, 0.0f);
		break;
	case Rect::BOTTOMLEFT:
		return Vector2(-half.x, half.y);
		break;
	case Rect::BOTTOMMID:
		return Vector2(0.0f, half.y);
		break;
	case Rect::BOTTOMRIGHT:
		return Vector2(half.x, half.y);
		break;
	default:
		std::cout << "This algnment doesn't exist" << std::endl;
		return Vector2(0.0f, 0.0f);
		break;
	}
}

Vector2 Rect::GetTopLeft()
{
	return *center - half;
}

std::vector<LineSegment> Rect::GetLinesToRender()
{
	std::vector<Vector2> corners;
	auto offset = GetOffsetByAlignment() / -2;

	For(x, 2)
	{
		For(y, 2)
		{
			corners.push_back(Vector2((-1 + (2*x)) * half.x, (-1 + (2*y)) * half.y));
		}
	}

	Matrix m = Matrix::GetRotationMatrix(GetRotation());
	m.SetOffset(offset);

	Vector2 c;
	if (center != nullptr)
	{
		c = *center;
	}

	For(i, corners.size())
	{
		corners[i] += offset * 2;
		corners[i] = m.GetTransformedVector(corners[i]);
		corners[i] = corners[i] + c -offset;
	}



	std::vector<LineSegment> lines;
	LineSegment left = LineSegment(corners[0], corners[1]);
	lines.push_back(left);
	LineSegment right = LineSegment(corners[2], corners[3]);
	lines.push_back(right);
	LineSegment top = LineSegment(corners[0], corners[2]);
	lines.push_back(top);
	LineSegment bot = LineSegment(corners[1], corners[3]);
	lines.push_back(bot);


	return lines;
}
