#ifndef  ROOMMANAGER_H
#define ROOMMANAGER_H

#include <SDL.h>
#include "Tile.h"
#include <iostream>
#include <random>
#include "MMath.h"

using namespace MATH;
class RoomManager
{

private:

	int currentRoomCount = 0;
	int roomCount = 10;  //change these numbers for # of rooms
	Tile* roomArray[10];
	Vec3 screenCoordsArray[10];
	SDL_Rect rectArray[10];

public:

	void GenerateRooms();
	void OnDestroy();
	void Render(SDL_Surface* surface, Matrix4 projection);

};

#endif
