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
	int splitRoomCount;
	int generationAttempts = 0;
	int splitRoomChanceRoll;
	int splitRoomMaxChance = 5; //K: adjust this value to change how frequently splitter rooms appear in generation, the higher the value, the less likely.
	bool directionArray[4] = {false, false, false, false};
	bool splitRoomExists = true;

	int roomCount = 100;  //change these numbers for # of rooms, includes starting room
	Tile* roomArray[100];
	Vec3 screenCoordsArray[100];
	SDL_Rect rectArray[100];

public:

	void GenerateRooms();
	void CreateBranches(int branches, int branchRoomNumber, int sideOrigin);
	void CreateRoom(int sideNumber, int roomNumber);
	void MoveRooms(int direction);
	void OnDestroy();
	void Render(SDL_Surface* surface, Matrix4 projection);
	void ResetValues();
};

#endif
