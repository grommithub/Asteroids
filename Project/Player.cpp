#include "Player.h"
#include <algorithm>
Player::Player() : collision(Circle(15.0f)), acceleration(0.2f), retardation(1.01), steeringSpeed(5.0f),left(false),right(false),up(false),shoot(false), canShoot(true), flameLength(0.0f), flameLengthMax(60.0f)
{
	collision.SetCenter(_position);
	collision.SetRotationReference(_rotation);

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



	thrustLines[0].points[0] = bottomRight.Tail() - (bottomRight.Tail() + bottomRight.Head()) * 0.5f;
	thrustLines[1].points[0] = bottomLeft.Tail() - (bottomLeft.Tail() + bottomLeft.Head()) * 0.5f;


}

void Player::OnKeyDown(int key)
{
	switch ((SDL_Keycode)key)
	{
	case SDLK_LEFT:
		left = true;
		break;
	case SDLK_RIGHT:
		right = true;
		break;
	case SDLK_UP:
		up = true;
		break;
	case SDLK_SPACE:
		shoot = true;
		break;
	default:
		break;
	}
}

void Player::OnKeyUp(int key)
{
	switch ((SDL_Keycode)key)
	{
	case SDLK_LEFT:
		left = false;
		break;
	case SDLK_RIGHT:
		right = false;
		break;
	case SDLK_UP:
		up = false;
		break;
	case SDLK_SPACE:
		shoot = false;
  		canShoot = true;
		break;
	default:
		break;
	}
}

void Player::Update()
{
	float rotationDelta = 0.0f;
	if (left) rotationDelta -= steeringSpeed;
	if (right) rotationDelta += steeringSpeed;
	AddRotation(rotationDelta);

	if (up)
	{
		auto up = Vector2::Up();
		auto rotatedUp = Matrix::GetRotationMatrix(_rotation).GetTransformedVector(up);

		velocity += rotatedUp * acceleration;
	}

	_position += velocity;
	velocity /= retardation;

}

bool Player::GetShoot()
{
	if (shoot && canShoot)
	{
		canShoot = false;
		return true;
	}
	return false;
}

std::vector<LineSegment> Player::GetLinesToRender()
{
	std::vector<LineSegment> lines = VectorShape::GetLinesToRender();

	Matrix m;
	m.SetScale(_scale);
	m.SetRotation(_rotation);
	m.SetOffset(_position);

	if (up)
	{
		flameLength += 0.5f;
		flameLength = std::min(flameLength, flameLengthMax);		
	}
	else
	{
		flameLength -= 1.5f;
		flameLength = std::max(0.0f, flameLength);
	}


	For(i, 2)
	{
		float f = std::max(flameLength + (-10.0f + (float)(rand() % 20)), 0.0f);
		thrustLines[0].points[1] = Vector2::Down() * f;
		thrustLines[1].points[1] = Vector2::Down() * f;

		LineSegment l = thrustLines[i];
		For(j, 2)
		{
			l.points[j] = m.GetTransformedVector(l.points[j]);
		}

		lines.push_back(l);
	}

	return lines;
}
