#ifndef ROOM_H
#define ROOM_H

#include "GameObject.h"
#include "Physics.h"
#include "Vector.h"
#include "Tile.h"

class Room : public GameObject, public Physics, public Tile	{
public:

	int height;
	int width;
	Room();
	~Room();
	Room(Tile(Vec3 pos_, Vec3 vel_, int height_, int width_));
	Room(Tile(Vec3 pos_, Vec3 vel_, int height_, int width_, SDL_Surface* image_));
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render()const;
	void HandleEvents(const SDL_Event& event);

};

#endif // !ROOM_H