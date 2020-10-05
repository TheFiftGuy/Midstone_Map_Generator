#ifndef TILE_H
#define TILE_H

#include "GameObject.h"
#include "Physics.h"
#include "Vector.h"
#include <SDL.h>

using namespace MATH;

class Tile : public GameObject, public Physics
{
public:
	int height;
	int width;
	Tile();
	~Tile();
	Tile(Vec3 pos_, Vec3 vel_, int height_, int width_);
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render()const;
	void HandleEvents(const SDL_Event& event);
	SDL_Surface* image;


};
#endif // !MAPONE_H


