#pragma once

#include "LineSegment.h"
#include <vector>
#include <SDL_opengl.h>
#include "Circle.h"

struct Colour
{
	unsigned char _r, _g, _b, _a;
	Colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
	{
		_r = r;
		_g = g;
		_b = b;
		_a = a;
	}
	void Set(Colour* col)
	{
		_r = col->_r;
		_g = col->_g;
		_b = col->_b;
		_a = col->_a;
	}
	void SetR(unsigned char r) { _r = r; }
	void SetG(unsigned char g) { _g = g; }
	void SetB(unsigned char b) { _b = b; }
	void SetA(unsigned char a) { _a = a; }
};

class Renderer
{


	std::vector<LineSegment> _lineEntries;

	float _lineWidth;
	Colour _drawColour;

public:
	Renderer();
	void Render(LineSegment& line);
	void Render(Circle* circle, float rotation);
	void Render(Circle* circle);
	void Render(LineSegment* line);

	void Render(std::vector<LineSegment*> lines);
	void Render(std::vector<LineSegment> lines);
	void SetDrawColour(Colour* col);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) { _drawColour._r = r; _drawColour._g = g; _drawColour._b = b; _drawColour._a = a; }
};

