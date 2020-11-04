#include "Renderer.h"
#include "Circle.h"

#define ToRadians(n) n / PI * 180
#define ToDegrees(n) n /180 * PI

#define For(i,N) for (int (i) = 0; (i) < (N); (i)++)

Renderer::Renderer() : _lineWidth(3.0f), _drawColour(Colour(255,255,255))
{

}

void Renderer::Render(LineSegment& line)
{
	Render(&line);
}

//void Renderer::Render(Circle* circle, float rotation)
//{
//	glBegin(GL_LINE_LOOP);
//
//	glVertex2f(circle->center->x, circle->center->y);
//
//	for (int i = 0; i < 360; i += 360 / 10)
//	{
//		float degInRad = i * 3.1415926f / 180;
//		glVertex2f(cos(degInRad + rotation * 3.1415962f / 180) * circle->radius + circle->center->x, sin(degInRad + rotation * 3.1415962f / 180) * circle->radius + circle->center->y);
//	}
//
//	glEnd();
//}

//void Renderer::Render(Circle* circle)
//{
//
//	glBegin(GL_LINE_LOOP);
//
//	for (int i = 0; i < 360; i+= 10)
//	{
//		float degInRad = i * 3.1415926f / 180;
//		glVertex2f(cos(degInRad) * circle->radius + circle->center->x, sin(degInRad) * circle->radius + circle->center->y);
//	}
//
//	glEnd();
//}

void Renderer::Render(LineSegment* line)
{
	glLineWidth(_lineWidth);
	glPointSize(10);


	glBegin(GL_LINES);
	SetDrawColour(&_drawColour);
	glVertex3f(line->Head().x, line->Head().y, 0.0f);
	SetDrawColour(&_drawColour);
	glVertex3f(line->Tail().x, line->Tail().y, 0.0f);
	glEnd();
}

void Renderer::Render(std::vector<LineSegment> lines)
{
	For(i, lines.size())
	{
		Render(lines[i]);
	}
}

void Renderer::SetDrawColour(Colour* col)
{
	glColor3ub(255, 255, 255);
}
