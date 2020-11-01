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
	int splitRoomMaxChance = 10; //K: adjust this value to change how frequently splitter rooms appear in generation, the higher the value, the less likely.
	bool directionArray[4] = {false, false, false, false};
	bool splitRoomExists = true;
	bool sucessfullyGen;
	bool resetInProgress;
	Tile* tempTile;

	int roomCount = 50;  //change these numbers for # of rooms, includes starting room
	Tile* roomArray[50];
	Vec3 screenCoordsArray[50];
	SDL_Rect rectArray[50];

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
