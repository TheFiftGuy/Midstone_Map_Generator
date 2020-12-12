#ifndef  ROOMMANAGER_H
#define ROOMMANAGER_H

#include <SDL.h>
#include "Tile.h"
#include <iostream>
#include <vector>
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
	int NewRoomCount = 0;
	int splitRoomChanceRoll;
	int splitRoomMaxChance = 25; //K: adjust this value to change how frequently splitter rooms appear in generation, the higher the value, the less likely.
	bool directionArray[4] = {false, false, false, false};
	bool splitRoomExists = true;
	bool sucessfullyGen;
	bool resetInProgress;
	bool initialRoomGen;
	Tile tempTile;

	int roomCount;
	std::vector<Tile> roomArray; 
	std::vector<Vec3> screenCoordsArray;
	std::vector<SDL_Rect> rectArray;
	

	SDL_Surface* tileImage = IMG_Load("WhiteBox.png"); //our testing rooms
	SDL_Surface* startRoom = IMG_Load("StartRoom.png");

	SDL_Surface* room1 = IMG_Load("RoomPictures/Room1.png"); //newly designed rooms
	SDL_Surface* room2 = IMG_Load("RoomPictures/Room2.png");
	SDL_Surface* room3 = IMG_Load("RoomPictures/Room3.png");
	SDL_Surface* room4 = IMG_Load("RoomPictures/Room4.png");
	SDL_Surface* room5 = IMG_Load("RoomPictures/Room5.png");
	SDL_Surface* room6 = IMG_Load("RoomPictures/Room6.png");
	SDL_Surface* room7 = IMG_Load("RoomPictures/Room7.png");
	SDL_Surface* room8 = IMG_Load("RoomPictures/Room8.png");
	SDL_Surface* room9 = IMG_Load("RoomPictures/Room9.png");
	SDL_Surface* roomBottom = IMG_Load("RoomPictures/BottomEnd.png");
	SDL_Surface* roomTop = IMG_Load("RoomPictures/TopEnd.png");
	SDL_Surface* roomLeft = IMG_Load("RoomPictures/LeftEnd.png");
	SDL_Surface* roomRight = IMG_Load("RoomPictures/RightEnd.png");
	SDL_Surface* roomCorridorH = IMG_Load("RoomPictures/HorizontalCorridor.png");
	SDL_Surface* roomCorridorV = IMG_Load("RoomPictures/VerticalCorridor.png");

public:
	void roomInput();
	void GenerateRooms();
	void SetRoomImages();
	void CreateBranches(int branches, int branchRoomNumber, int sideOrigin);
	void CreateRoom(int sideNumber, int roomNumber);
	void MoveRooms(int direction);
	void OnDestroy();
	void Render(SDL_Surface* surface, Matrix4 projection);
	void ResetValues();
};

#endif
