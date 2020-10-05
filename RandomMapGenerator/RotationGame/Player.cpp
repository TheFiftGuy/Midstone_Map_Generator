#include "Player.h"
#include "Tile.h"
Player::Player() :Physics(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f)
{
}
Player::~Player()
{

}
Player::Player(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_) {
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;

	mass = mass_;
}

bool Player::OnCreate()
{
	return false;
}

void Player::OnDestroy()
{

}

void Player::Update(const float deltaTime)
{
	Physics::Update(deltaTime);

	if (MoveState == 0) {
		SetVelocity(0.0,0.0,0.0);
	}
	if (MoveState == 1) {
		SetVelocity(10.0, 0.0, 0.0);
	}
	if (MoveState == 2) {
		SetVelocity(-10.0, 0.0, 0.0);
	}
	if (MoveState == 3) {
		SetVelocity(0.0, 10.0, 0.0);
	}
	if (MoveState == 4) {
		SetVelocity(0.0, -10.0, 0.0);
	}
	if (MoveState == 8) {
		degrees1 += 10;
	}
	if (MoveState == 9) {
		degrees1 -= 10;
	}
}

void Player::Render() const
{

}
void Player::HandleEvents(const SDL_Event& event)
{
switch (event.type) {
		/* Look for a keypress */
	case SDL_KEYDOWN:
		/* Check the SDLKey values and move change the coords */
		switch (event.key.keysym.sym) {
		case SDLK_d:
			MoveState = 1;
			break;
		case SDLK_a:
			MoveState = 2;
			break;
		case SDLK_w:
			MoveState = 3;
			break;
		case SDLK_s:
			MoveState = 4;
			break;
		case SDLK_q:
			RotateLevelLeft = true;
			std::cout << SDL_GetKeyName(event.key.keysym.sym) << " is pressed." << std::endl;
			break;
		case SDLK_e:
			RotateLevelRight = true;
			std::cout << SDL_GetKeyName(event.key.keysym.sym) << " is pressed." << std::endl;
		default:
			break;
		}
	//reverts velocity when you let go of key.
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_d:
			if (GetVelocity().x > 0)
				MoveState = 0;
			break;
		case SDLK_a:
			if (GetVelocity().x < 0)
				MoveState = 0;
			break;
		case SDLK_w:
			if (GetVelocity().y > 0)
				MoveState = 0;
			break;
		case SDLK_s:
			if (GetVelocity().y < 0)
				MoveState = 0;
			break;
		default:
			break;
		}
		break;

		default:
			break;
	}
}

void Player::CheckCollisions(Tile tile_)
{
	if (pos.x < tile_.GetPosition().x + tile_.width && pos.x > tile_.GetPosition().x - tile_.width && pos.y < tile_.GetPosition().y + tile_.height && pos.y > tile_.GetPosition().y - tile_.height) {
		if (pos.y + 2 > tile_.GetPosition().y + tile_.height) {
			vel.y = 0;
		}
		if (pos.y - 2 < tile_.GetPosition().y - tile_.height) {
			vel.y = vel.y * -1;
			pos.y = pos.y - 1;
		}
		if (pos.x + 2 > tile_.GetPosition().x + tile_.height) {
			vel.x = vel.x * -1;
			pos.x = pos.x + 1;
		}
		if (pos.x - 2 < tile_.GetPosition().x - tile_.height) {
			vel.x = vel.x * -1;
			pos.x = pos.x - 1;
		}

	}
}
