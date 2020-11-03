#include "Player.h"

Player::Player()
{
	LineSegment topLeft;

	topLeft.Head() = Vector2(0.0f, -30.0f);
	topLeft.Tail() = Vector2(-15.0f, 15.0f);

	LineSegment topRight;

	topRight.Head() = Vector2(0.0f, -30.0f);
	topRight.Tail() = Vector2(15.0f, 15.0f);

	LineSegment bottomLeft;

	bottomLeft.Tail() = topLeft.Tail();

	LineSegment bottomRight;

	bottomRight.Tail() = topRight.Tail();


	_lines.push_back(topLeft); _lines.push_back(topRight);
	_lines.push_back(bottomLeft); _lines.push_back(bottomRight);
}
