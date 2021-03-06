#include "RoomManager.h"
#include "Utility.h"



void RoomManager::roomInput(){ //D This is where user input for the rooms is done - entire section done by D
	
	std::cout << "How many rooms do you want?" << endl;
	std::cout << "Input:";
	std::cin >> roomCount;
	//testing
	while (!cin) { //triggers if user writes anything that is not a number - Note if user writes " 15blahblah65" code will run with "15"

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "ERROR: Please try again, numbers only" << endl;

		std::cout << "How many rooms do you want?" << endl;
		std::cout << "Input:";
		std::cin >> roomCount;
	}

	while (roomCount > 180) /*anything more than 180 takes too long*/ {
		std::cout << "ERROR: Please try again. The number of rooms must be < 180" << endl;
		std::cout << "How many rooms do you want?" << endl;
		std::cout << "Input:";
		std::cin >> roomCount;
	}

	std::cout << "I want " << roomCount << " rooms." << endl; //just writes a message with the # of rooms input-ed

	//this makes all the arrays/vectors as large as we inputed
	roomArray.resize(roomCount);
	screenCoordsArray.resize(roomCount);
	rectArray.resize(roomCount);

	for (int i = 0; i < roomCount; i++) {
		roomArray.push_back(Tile());
	}
	for (int i = 0; i < roomCount; i++) {
		screenCoordsArray.push_back(Vec3());
	}
	for (int i = 0; i < roomCount; i++) {
		rectArray.push_back(SDL_Rect());
	}


}


void RoomManager::GenerateRooms()
{
	RoomManager::roomInput(); //D how many rooms (see above)

	// Runs until the room count is met
	while (currentRoomCount < roomCount)
	{
		// Create start room
		if (currentRoomCount == 0)
		{
			roomArray[0] = Tile(Vec3(400.0f, 400.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 50, 50, startRoom);
			currentRoomCount++;
			resetInProgress = false;

			// Determines how many branches out from the starting room
			numberOfStartingBranches = Utility::RandomNumberGenerator(1, 4);
			std::cout << "Starting Branches: " << numberOfStartingBranches << std::endl;

			for (int i = 0; i < numberOfStartingBranches; i++)
			{
				if (resetInProgress == false)
				{
					// checks if the generator has already generated rooms in that direction
					int direction = Utility::RandomNumberGenerator(0, 3);

					if (directionArray[direction] == true)
					{
						i--;
					}
					else
					{
						directionArray[direction] = true;
						CreateRoom(direction + 1, 0);
						if (resetInProgress == false)
						{
							splitRoomCount++;
						}
					}
				}
			}
		}
		else
		{
			//K: the room creator currently uses the amount of split paths to keep an order of generation between each path, as they will all be generated in a sequence 
			//(i.e. path 1 consists of rooms 2, 4, 6, 8 etc., path 2 consists of rooms 3, 5, 7, 9 etc. on a split of 2 different paths)
			CreateRoom(Utility::RandomNumberGenerator(1, 4), currentRoomCount - splitRoomCount);
		}
		//K: this keeps track of how many attempts the generator has made and force resets it if it fails to finish generating within an amount of attempts. (10x the amount of rooms that should be generated)
		generationAttempts++;
		if (generationAttempts > roomCount * 10)
		{
			std::cout << "Error: Map encountered a problem and was unable to generate in " << generationAttempts << " attempts. (Generate Rooms)" << std::endl << std::endl;;
			resetInProgress = true;
			ResetValues();
		}
	}
}

void RoomManager::CreateRoom(int sideNumber, int roomNumber)
{
	bool openSpace = true;

	switch (sideNumber)
	{
	case 1:  //Up
		tempTile = Tile(Vec3(roomArray[roomNumber].GetPosition().x, roomArray[roomNumber].GetPosition().y + 50.0f, roomArray[roomNumber].GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50, tileImage);
		
		for (int i = 0; i < currentRoomCount; i++)
		{
			if (roomArray[i].GetPosition().x == tempTile.GetPosition().x && roomArray[i].GetPosition().y == tempTile.GetPosition().y) //D this checks every room generated so far, to see if its located where tempTile wants to go
			{
				openSpace = false;
			}
		}

		if (openSpace == true)
		{
			// Set directions to decide which image to use
			tempTile.Down = true;
			roomArray[roomNumber].Up = true;

			roomArray[currentRoomCount] = tempTile;
			currentRoomCount++;
			sucessfullyGen = true;

			//K: Rolls a chance based on the MaxChance variable for deciding if the newly created room should be a split room or not
			splitRoomChanceRoll = Utility::RandomNumberGenerator(1, splitRoomMaxChance);
			if (splitRoomChanceRoll == 1)
			{
				std::cout << "Split Room Created" << std::endl << std::endl;
				int numberOfBranches = Utility::RandomNumberGenerator(1, 2);
				CreateBranches(numberOfBranches, currentRoomCount, sideNumber);
				numberOfBranches = NULL;
			}
		}
		if (openSpace == false)
		{
			sucessfullyGen = false;
		}
		break;

	case 2: //Right
		tempTile = Tile(Vec3(roomArray[roomNumber].GetPosition().x + 50.0f, roomArray[roomNumber].GetPosition().y, roomArray[roomNumber].GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50, tileImage);
		//TempTileArray[NewRoomCount + 1] = tempTile;
		for (int i = 0; i < currentRoomCount; i++)
		{
			if (roomArray[i].GetPosition().x == tempTile.GetPosition().x && roomArray[i].GetPosition().y == tempTile.GetPosition().y)
			{
				openSpace = false;
			}
		}

		if (openSpace == true)
		{
			// Set directions to decide which image to use
			tempTile.Left = true;
			roomArray[roomNumber].Right = true;

			roomArray[currentRoomCount] = tempTile;
			currentRoomCount++;
			sucessfullyGen = true;
			//K: Rolls a chance based on the MaxChance variable for deciding if the newly created room should be a split room or not
			splitRoomChanceRoll = Utility::RandomNumberGenerator(1, splitRoomMaxChance);
			if (splitRoomChanceRoll == 1)
			{
				std::cout << "Split Room Created" << std::endl << std::endl;
				int numberOfBranches = Utility::RandomNumberGenerator(1, 2);
				CreateBranches(numberOfBranches, currentRoomCount, sideNumber);
				numberOfBranches = NULL;
			}
		}
		if (openSpace == false)
		{
			sucessfullyGen = false;
		}
		break;

	case 3: //Down
		tempTile = Tile(Vec3(roomArray[roomNumber].GetPosition().x, roomArray[roomNumber].GetPosition().y - 50.0f, roomArray[roomNumber].GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50, tileImage);
		//TempTileArray[NewRoomCount + 1] = tempTile;
		for (int i = 0; i < currentRoomCount; i++)
		{
			if (roomArray[i].GetPosition().x == tempTile.GetPosition().x && roomArray[i].GetPosition().y == tempTile.GetPosition().y)
			{
				openSpace = false;
			}
		}

		if (openSpace == true)
		{
			// Set directions to decide which image to use
			tempTile.Up = true;
			roomArray[roomNumber].Down = true;

			roomArray[currentRoomCount] = tempTile;
			currentRoomCount++;
			sucessfullyGen = true;

			//K: Rolls a chance based on the MaxChance variable for deciding if the newly created room should be a split room or not
			splitRoomChanceRoll = Utility::RandomNumberGenerator(1, splitRoomMaxChance);
			if (splitRoomChanceRoll == 1)
			{
				std::cout << "Split Room Created" << std::endl << std::endl;
				int numberOfBranches = Utility::RandomNumberGenerator(1, 2);
				CreateBranches(numberOfBranches, currentRoomCount, sideNumber);
				numberOfBranches = NULL;
			}
		}
		if (openSpace == false)
		{
			sucessfullyGen = false;
		}
		break;

	case 4: //Left
		tempTile = Tile(Vec3(roomArray[roomNumber].GetPosition().x - 50.0f, roomArray[roomNumber].GetPosition().y, roomArray[roomNumber].GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50, tileImage);
		//TempTileArray[NewRoomCount + 1] = tempTile;
		for (int i = 0; i < currentRoomCount; i++)
		{
			//std::cout << tempTile->GetPosition().x << ", " << tempTile->GetPosition().y << ", " << tempTile->GetPosition().z << " " << roomArray[i]->GetPosition().x << ", " << roomArray[i]->GetPosition().y << ", " << roomArray[i]->GetPosition().z << std::endl;

			if (roomArray[i].GetPosition().x == tempTile.GetPosition().x && roomArray[i].GetPosition().y == tempTile.GetPosition().y)
			{
				openSpace = false;
			}
		}

		if (openSpace == true)
		{
			// Set directions to decide which image to use
			tempTile.Right = true;
			roomArray[roomNumber].Left = true;

			roomArray[currentRoomCount] = tempTile;
			currentRoomCount++;
			sucessfullyGen = true;

			//K: Rolls a chance based on the MaxChance variable for deciding if the newly created room should be a split room or not
			splitRoomChanceRoll = Utility::RandomNumberGenerator(1, splitRoomMaxChance);
			if (splitRoomChanceRoll == 1)
			{
				std::cout << "Split Room Created" << std::endl << std::endl;
				int numberOfBranches = Utility::RandomNumberGenerator(1, 2);
				CreateBranches(numberOfBranches, currentRoomCount, sideNumber);
				numberOfBranches = NULL;
			}
		}
		if (openSpace == false)
		{
			sucessfullyGen = false;
		}

		break;
	}
}

void RoomManager::CreateBranches(int branches, int branchRoomNumber, int sideOrigin)
{
	bool branchDirectionArray[4] = { false, false, false, false };
	//K: switch statement to check which side the creator of the splitting tile is from, to avoid attempting to generate on top of the already existing path it came from.
	switch (sideOrigin)
	{
	case 1: //so if "this room" was a "generate up" room, there is no space "down"
		branchDirectionArray[2] = true;
		break;
	case 2: // ^ same but right
		branchDirectionArray[3] = true;
		break;
	case 3:// ect...
		branchDirectionArray[0] = true;
		break;
	case 4:
		branchDirectionArray[1] = true;
		break;
	}

	for (int i = 0; i < branches; i++)
	{
		generationAttempts++;
		//K: this is here to stop it from continuing to do stuff from this loop if a reset happens
		if (resetInProgress == false)
		{
			// checks if the generator has already generated rooms in that direction
			int direction = Utility::RandomNumberGenerator(0, 3);

			if (branchDirectionArray[direction] == true)
			{
				i--;
			}
			else
			{
				//K: checks if adding a branch room would exceed the max number of rooms allowed, if this is not the case, it will attempt to generate the room.
				if (branchRoomNumber - 1 >= 0 && currentRoomCount != roomCount && currentRoomCount != 0) {
					CreateRoom(direction + 1, branchRoomNumber - 1);
					//K: if the room succesfully generates, its direction is added to the split rooms array to inform that the side is now occupied by a room
					if (sucessfullyGen == true && resetInProgress == false)
					{
						branchDirectionArray[direction] = true;
						splitRoomCount++;
					}
					//K: if the room fails to generate, then it likely means that another room from somewhere else is blocking the path, meaning that the space should be marked as occupied.
					if (sucessfullyGen == false && resetInProgress == false)
					{
						branchDirectionArray[direction] = true;
						i--;
					}
				}
			}
		}
		//K: this keeps track of how many attempts the generator has made and force resets it if it fails to finish generating within an amount of attempts. (10x the amount of rooms that should be generated)
		if (generationAttempts > roomCount * 10) {
			std::cout << "Error: Map encountered a problem and was unable to generate in " << generationAttempts << " attempts. (create branches)" << std::endl << std::endl;;
			resetInProgress = true;
			ResetValues();
			break;
		}
	}

	//K: clears the direction array for future branch rooms after finishing
	for (int i = 0; i < 4; i++)
	{
		branchDirectionArray[i] = NULL;
	}
}

void RoomManager::SetRoomImages(){ //D This decides what Image each room will have, depending on where the entrances/exits of the rooms are.

	//Loop for each room, to find what criteria the rooms fit, then assigns one accordingly 
	
	for (int i = 0; i < roomCount; i++) {

		
		if (i == 0) {
			//starting room will Stay as the Red image
			continue;
		}
		if (roomArray[i].Up == true && roomArray[i].Right == false && roomArray[i].Down == false && roomArray[i].Left == false) { //D Bottom End room

			roomArray[i].SetImage(roomBottom);
			continue;
		}
		if (roomArray[i].Up == false && roomArray[i].Right == true && roomArray[i].Down == false && roomArray[i].Left == true) { //D Horizontal Corridor

			roomArray[i].SetImage(roomCorridorH);
			continue;
		}
		if (roomArray[i].Up == false && roomArray[i].Right == true && roomArray[i].Down == false && roomArray[i].Left == false) { //D Left End room

			roomArray[i].SetImage(roomLeft);
			continue;
		}
		if (roomArray[i].Up == false && roomArray[i].Right == false && roomArray[i].Down == false && roomArray[i].Left == true) { //D Right End room

			roomArray[i].SetImage(roomRight);
			continue;
		}
		if (roomArray[i].Up == false && roomArray[i].Right == false && roomArray[i].Down == true && roomArray[i].Left == false) { //D  Top End Room

			roomArray[i].SetImage(roomTop);
			continue;
		}
		if (roomArray[i].Up == true && roomArray[i].Right == false && roomArray[i].Down == true && roomArray[i].Left == false) { //D  Vertical Corridor Room

			roomArray[i].SetImage(roomCorridorV);
			continue;
		}
		//D for the next 9 rooms, the names come from imaging a 3*3 grid like a numpad, where 1 is at the top left, and 9 is bottom right
		if (roomArray[i].Up == false && roomArray[i].Right == true && roomArray[i].Down == true && roomArray[i].Left == false) { //D Top left  room

			roomArray[i].SetImage(room1);
			continue;
		}
		if (roomArray[i].Up == false && roomArray[i].Right == true && roomArray[i].Down == true && roomArray[i].Left == true) { //D Top middle room

			roomArray[i].SetImage(room2);
			continue;
		}
		if (roomArray[i].Up == false && roomArray[i].Right == false && roomArray[i].Down == true && roomArray[i].Left == true) { //D Top right  room

			roomArray[i].SetImage(room3);
			continue;
		}
		if (roomArray[i].Up == true && roomArray[i].Right == true && roomArray[i].Down == true && roomArray[i].Left == false) { //D Middle left room

			roomArray[i].SetImage(room4);
			continue;
		}
		if (roomArray[i].Up == true && roomArray[i].Right == true && roomArray[i].Down == true && roomArray[i].Left == true) { //D  Middle room

			roomArray[i].SetImage(room5);
			continue;
		}
		if (roomArray[i].Up == true && roomArray[i].Right == false && roomArray[i].Down == true && roomArray[i].Left == true) { //D  Middle right room

			roomArray[i].SetImage(room6);
			continue;
		}
		if (roomArray[i].Up == true && roomArray[i].Right == true && roomArray[i].Down == false && roomArray[i].Left == false) { //D  Bottom Left room

			roomArray[i].SetImage(room7);
			continue;
		}
		if (roomArray[i].Up == true && roomArray[i].Right == true && roomArray[i].Down == false && roomArray[i].Left == true) { //D  Bottom middle room

			roomArray[i].SetImage(room8);
			continue;
		}
		if (roomArray[i].Up == true && roomArray[i].Right == false && roomArray[i].Down == false && roomArray[i].Left == true) { //D  Bottom right room

			roomArray[i].SetImage(room9);
			continue;
		}
	}

}

void RoomManager::MoveRooms(int direction)
{
	for (int i = 0; i < roomCount; i++)
	{
		switch (direction)
		{
		//H - Move rooms in the direction given from the event handler. 1: Up, 2: Right, 3: Down, 4: Left
		case 1:
			roomArray[i].SetPosition(roomArray[i].GetPosition().x, roomArray[i].GetPosition().y + 5, 0);
			break;
		case 2:
			roomArray[i].SetPosition(roomArray[i].GetPosition().x + 5, roomArray[i].GetPosition().y, 0);
			break;
		case 3:
			roomArray[i].SetPosition(roomArray[i].GetPosition().x, roomArray[i].GetPosition().y - 5, 0);
			break;
		case 4:
			roomArray[i].SetPosition(roomArray[i].GetPosition().x - 5, roomArray[i].GetPosition().y, 0);
			break;
		}
	}
}

void RoomManager::OnDestroy()
{
	for (int i = 0; i < roomCount; i++)
	{
		roomArray[i].OnDestroy();
	}
	free(tileImage);
	delete tileImage;
	
}

void RoomManager::Render(SDL_Surface* surface, Matrix4 projection)
{
	for (int i = 0; i < roomCount; i++)
	{
		screenCoordsArray[i] = projection * roomArray[i].GetPosition();
		rectArray[i].h = roomArray[i].image->h;
		rectArray[i].w = roomArray[i].image->w;
		rectArray[i].x = screenCoordsArray[i].x - 25.0f; //D the -25's here are so that the origin of the image is at the center, since the image is 50x50 
		rectArray[i].y = screenCoordsArray[i].y - 25.0f; //D  (instead of the origin being at the bottom left)

		SDL_BlitSurface(roomArray[i].image, nullptr, surface, &rectArray[i]);
	}
}

void RoomManager::ResetValues()
{
	// sets all values to their original values
	currentRoomCount = 0;
	splitRoomCount = 0;
	generationAttempts = 0;

	for (int i = 0; i < 4; i++)
	{
		directionArray[i] = false;
	}
	roomArray[0].SetImage(tileImage);
	for (int i = 0; i < roomCount; i++)
	{
		roomArray[i].SetPosition(400.0f, 400.0f, 0.0f);
		screenCoordsArray[i] = Vec3(0.0f, 0.0f, 0.0f);
		rectArray[i].h = 0.0f;
		rectArray[i].w = 0.0f;
		rectArray[i].x = 0.0f;
		rectArray[i].y = 0.0f;
	}
}
