#include "RoomManager.h"

void RoomManager::GenerateRooms()
{
	while (currentRoomCount < roomCount)
	{
		if (currentRoomCount == 0)
		{
			roomArray[0] = new Tile(Vec3(400.0f, 400.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 50, 50, IMG_Load("StartRoom.png"));
			currentRoomCount++;
		}
		else
		{
			// current room count is 
			bool openSpace = true;
			Tile* tempTile;

			// generate random number
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distr(1, 4);

			switch (distr(gen))
			{
			case 1:
				// nothing in the room array at current room count which is why its an error
				tempTile = new Tile(Vec3(roomArray[currentRoomCount - 1]->GetPosition().x, roomArray[currentRoomCount - 1]->GetPosition().y + 50.0f, roomArray[currentRoomCount - 1]->GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50);

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
				}

				break;

			case 2:
				tempTile = new Tile(Vec3(roomArray[currentRoomCount - 1]->GetPosition().x + 50.0f, roomArray[currentRoomCount - 1]->GetPosition().y, roomArray[currentRoomCount - 1]->GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50);

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
				}
				break;

			case 3:
				tempTile = new Tile(Vec3(roomArray[currentRoomCount - 1]->GetPosition().x, roomArray[currentRoomCount - 1]->GetPosition().y - 50.0f, roomArray[currentRoomCount - 1]->GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50);

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
				}
				break;

			case 4:
				tempTile = new Tile(Vec3(roomArray[currentRoomCount - 1]->GetPosition().x - 50.0f, roomArray[currentRoomCount - 1]->GetPosition().y, roomArray[currentRoomCount - 1]->GetPosition().z), Vec3(0.0f, 0.0f, 0.0f), 50, 50);

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
				}
				break;
			}
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
