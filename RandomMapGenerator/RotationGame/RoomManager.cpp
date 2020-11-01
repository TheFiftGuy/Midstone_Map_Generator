#include "RoomManager.h"
#include "Utility.h"

void RoomManager::GenerateRooms()
{
	while (currentRoomCount < roomCount)
	{
		if (currentRoomCount == 0)
		{
			roomArray[0] = new Tile(Vec3(400.0f, 400.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 50, 50, IMG_Load("StartRoom.png"));
			currentRoomCount++;

			// Determines how many branches out from the starting room
			numberOfStartingBranches = Utility::RandomNumberGenerator(1, 4);
			std::cout << "Starting Branches: " << numberOfStartingBranches << std::endl;

			for (int i = 0; i < numberOfStartingBranches; i++)
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
					splitRoomCount++;
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
			std::cout << "Error: Map encountered a problem and was unable to generate in " << generationAttempts << " attempts." << std::endl << std::endl;;
			ResetValues();
		}
	}
}

void RoomManager::CreateRoom(int sideNumber, int roomNumber)
{
	bool openSpace = true;
	Tile* tempTile;

	switch (sideNumber)
	{
	case 1:
		tempTile = new Tile(Vec3(roomArray[roomNumber]->GetPosition().x, roomArray[roomNumber]->GetPosition().y + 50.0f, roomArray[roomNumber]->GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50);

		for (int i = 0; i < currentRoomCount; i++)
		{
			if (roomArray[i]->GetPosition().x == tempTile->GetPosition().x && roomArray[i]->GetPosition().y == tempTile->GetPosition().y)
			{
				openSpace = false;
			}
		}

		if (openSpace == true)
		{
			roomArray[currentRoomCount] = tempTile;
			std::cout << "Up" << std::endl;
			currentRoomCount++;
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
		break;

	case 2:
		tempTile = new Tile(Vec3(roomArray[roomNumber]->GetPosition().x + 50.0f, roomArray[roomNumber]->GetPosition().y, roomArray[roomNumber]->GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50);

		for (int i = 0; i < currentRoomCount; i++)
		{
			if (roomArray[i]->GetPosition().x == tempTile->GetPosition().x && roomArray[i]->GetPosition().y == tempTile->GetPosition().y)
			{
				openSpace = false;
			}
		}

		if (openSpace == true)
		{
			roomArray[currentRoomCount] = tempTile;
			std::cout << "Right" << std::endl;
			currentRoomCount++;
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
		break;

	case 3:
		tempTile = new Tile(Vec3(roomArray[roomNumber]->GetPosition().x, roomArray[roomNumber]->GetPosition().y - 50.0f, roomArray[roomNumber]->GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50);

		for (int i = 0; i < currentRoomCount; i++)
		{
			if (roomArray[i]->GetPosition().x == tempTile->GetPosition().x && roomArray[i]->GetPosition().y == tempTile->GetPosition().y)
			{
				openSpace = false;
			}
		}

		if (openSpace == true)
		{
			roomArray[currentRoomCount] = tempTile;
			std::cout << "Down" << std::endl;
			currentRoomCount++;
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
		break;

	case 4:
		tempTile = new Tile(Vec3(roomArray[roomNumber]->GetPosition().x - 50.0f, roomArray[roomNumber]->GetPosition().y, roomArray[roomNumber]->GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50);

		for (int i = 0; i < currentRoomCount; i++)
		{
			//std::cout << tempTile->GetPosition().x << ", " << tempTile->GetPosition().y << ", " << tempTile->GetPosition().z << " " << roomArray[i]->GetPosition().x << ", " << roomArray[i]->GetPosition().y << ", " << roomArray[i]->GetPosition().z << std::endl;

			if (roomArray[i]->GetPosition().x == tempTile->GetPosition().x && roomArray[i]->GetPosition().y == tempTile->GetPosition().y)
			{
				openSpace = false;
			}
		}

		if (openSpace == true)
		{
			roomArray[currentRoomCount] = tempTile;
			std::cout << "Left" << std::endl;
			currentRoomCount++;
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
		break;
	}
}

void RoomManager::CreateBranches(int branches, int branchRoomNumber, int sideOrigin)
{
	bool branchDirectionArray[4] = { false, false, false, false };
	//K: switch statement to check which side the creator of the splitting tile is from, to avoid attempting to generate on top of the already existing path it came from.
	switch (sideOrigin)
	{
	case 1:
		branchDirectionArray[2] = true;
		break;
	case 2:
		branchDirectionArray[3] = true;
		break;
	case 3:
		branchDirectionArray[0] = true;
		break;
	case 4:
		branchDirectionArray[1] = true;
		break;
	}

	for (int i = 0; i < branches; i++)
	{
		// checks if the generator has already generated rooms in that direction
		int direction = Utility::RandomNumberGenerator(0, 3);

		if (branchDirectionArray[direction] == true)
		{
			i--;
		}
		else
		{
			branchDirectionArray[direction] = true;
			CreateRoom(direction + 1, branchRoomNumber - 1);
			splitRoomCount++;
		}
		generationAttempts++;
		if (generationAttempts > roomCount * 10) {
			std::cout << "Error: Map encountered a problem and was unable to generate in " << generationAttempts << " attempts." << std::endl << std::endl;;
			ResetValues();
			break;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		branchDirectionArray[i] = NULL;
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
			roomArray[i]->SetPosition(roomArray[i]->GetPosition().x, roomArray[i]->GetPosition().y + 5, 0);
			break;
		case 2:
			roomArray[i]->SetPosition(roomArray[i]->GetPosition().x + 5, roomArray[i]->GetPosition().y, 0);
			break;
		case 3:
			roomArray[i]->SetPosition(roomArray[i]->GetPosition().x, roomArray[i]->GetPosition().y - 5, 0);
			break;
		case 4:
			roomArray[i]->SetPosition(roomArray[i]->GetPosition().x - 5, roomArray[i]->GetPosition().y, 0);
			break;
		}
	}
}

void RoomManager::OnDestroy()
{
	for (int i = 0; i < roomCount; i++)
	{
		delete roomArray[i];
	}
	delete roomArray;
}

void RoomManager::Render(SDL_Surface* surface, Matrix4 projection)
{
	for (int i = 0; i < roomCount; i++)
	{
		screenCoordsArray[i] = projection * roomArray[i]->GetPosition();
		rectArray[i].h = roomArray[i]->image->h;
		rectArray[i].w = roomArray[i]->image->w;
		rectArray[i].x = screenCoordsArray[i].x - 25.0f; //D the -25's here are so that the origin of the image is at the center, since the image is 50x50 
		rectArray[i].y = screenCoordsArray[i].y - 25.0f; //D  (instead of the origin being at the bottom left)

		SDL_BlitSurface(roomArray[i]->image, nullptr, surface, &rectArray[i]);
	}
}

void RoomManager::ResetValues()
{
	currentRoomCount = 0;
	splitRoomCount = 0;
	generationAttempts = 0;

	for (int i = 0; i < 4; i++)
	{
		directionArray[i] = false;
	}

	for (int i = 0; i < roomCount; i++)
	{
		roomArray[i] = NULL;
		screenCoordsArray[i] = Vec3(0.0f, 0.0f, 0.0f);
		rectArray[i].h = 0.0f;
		rectArray[i].w = 0.0f;
		rectArray[i].x = 0.0f;
		rectArray[i].y = 0.0f;
	}
}
