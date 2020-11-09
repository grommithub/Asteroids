#include "Player.h"

Player::Player() : collisionBox(Rect(20.0f, 30.0f)), acceleration(0.2f), retardation(1.01), steeringSpeed(5.0f),left(false),right(false),up(false),shoot(false), canShoot(true)
{
	collisionBox.SetCenter(_position);
	collisionBox.SetRotationReference(_rotation);

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
