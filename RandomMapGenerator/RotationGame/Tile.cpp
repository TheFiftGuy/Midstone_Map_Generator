#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{

}

Tile::Tile(Vec3 pos_, Vec3 vel_, int height_, int width_)
{
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	height = height_;
	width = width_;
}

bool Tile::OnCreate()
{
	return false;
}

void Tile::OnDestroy()
{
}

void Tile::Update(const float deltaTime)
{

}

void Tile::Render() const
{
}



void Tile::HandleEvents(const SDL_Event& event)
{
	
}
