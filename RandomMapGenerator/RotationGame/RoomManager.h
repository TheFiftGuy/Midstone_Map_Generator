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
	int numberOfStartingBranches;
	bool directionArray[4] = {false, false, false, false};

	int roomCount = 20;  //change these numbers for # of rooms, includes starting room
	Tile* roomArray[20];
	Vec3 screenCoordsArray[20];
	SDL_Rect rectArray[20];

public:

	void GenerateRooms();
	void CreateRoom(int sideNumber, int roomNumber);
	void OnDestroy();
	void Render(SDL_Surface* surface, Matrix4 projection);
	void ResetValues();
};

#endif
