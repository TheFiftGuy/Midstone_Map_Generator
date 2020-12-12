#ifndef TILE_H
#define TILE_H

#include "GameObject.h"
#include "Physics.h"
#include "Vector.h"
#include <SDL.h>
#include <SDL_Image.h>

using namespace MATH;

class Tile : public GameObject, public Physics
{

	//D scott tesint stuff here
	//CHANGES HERE
	//Tile(const Tile&);
	//Tile& operator = (const Tile&);

public:
	int height;
	int width;


	bool Up = false;
	bool Right = false;
	bool Down = false;
	bool Left = false;

	Tile();
	~Tile();
	Tile(Vec3 pos_, Vec3 vel_, int height_, int width_);
	Tile(Vec3 pos_, Vec3 vel_, int height_, int width_, SDL_Surface* image_);
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render()const;
	void HandleEvents(const SDL_Event& event);
	void SetImage(SDL_Surface* ImageName);

	SDL_Surface* image;
};
#endif // !MAPONE_H


