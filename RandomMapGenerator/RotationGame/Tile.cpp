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

	//D removed for now, now adding new image feature - I dont think this was being used?
	//image = IMG_Load("WhiteBox.png");
}

Tile::Tile(Vec3 pos_, Vec3 vel_, int height_, int width_, SDL_Surface* image_)
{
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	height = height_;
	width = width_;

	image = image_;
}

bool Tile::OnCreate()
{
	return false;
}

void Tile::OnDestroy()
{
	delete image;
	image = nullptr;
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

void Tile::SetImage(SDL_Surface* ImageName)
{
	image = ImageName;
}
