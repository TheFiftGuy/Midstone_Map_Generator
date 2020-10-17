#include "Room.h"

Room::Room()
{

}

Room::~Room()
{

}

Room::Room(Tile(Vec3 pos_, Vec3 vel_, int height_, int width_))
{
	
}

Room::Room(Tile(Vec3 pos_, Vec3 vel_, int height_, int width_, SDL_Surface* image_))
{
}

bool Room::OnCreate()
{
	return false;
}

void Room::OnDestroy()
{
}

void Room::Update(const float deltaTime)	{


}

void Room::Render() const
{
}

void Room::HandleEvents(const SDL_Event& event)
{
}
