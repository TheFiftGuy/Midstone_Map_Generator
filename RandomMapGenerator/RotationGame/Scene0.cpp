#include "Scene0.h"
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>

Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	
	mRender = nullptr;
	
}

Scene0::~Scene0(){
}

bool Scene0::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	Matrix4 ndc = MMath::viewportNDC(w, h);//D Resolution is 800x800
	Matrix4 ortho = MMath::orthographic(0.0f, 800.0f, 0.0f, 800.0f,0.0f,1.0f);	//D To make things simple resolution and orthgraphic are the same, for the rest of the...
	projection =  ndc * ortho;													//D ...project we will consider 50 pixels as 1 imgaginary "unit" in a cartesian plane
	Scene0RoomManager = new RoomManager();
	Scene0RoomManager->GenerateRooms();
	Scene0RoomManager->SetRoomImages();

	return true;
}

void Scene0::OnDestroy()
{
	Scene0RoomManager->OnDestroy();
}

void Scene0::Update(const float time)
{	

}

void Scene0::Render()
{
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

	Scene0RoomManager->Render(screenSurface, projection);
	SDL_RenderPresent(mRender);
	SDL_UpdateWindowSurface(window);
}

void Scene0::HandleEvents(const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_E:
			Reset();
			break;
		case SDL_SCANCODE_W:
			Scene0RoomManager->MoveRooms(1);
			ClearScreen();
			break;
		case SDL_SCANCODE_D:
			Scene0RoomManager->MoveRooms(2);
			ClearScreen();
			break;
		case SDL_SCANCODE_S:
			Scene0RoomManager->MoveRooms(3);
			ClearScreen();
			break;
		case SDL_SCANCODE_A:
			Scene0RoomManager->MoveRooms(4);
			ClearScreen();
			break;
		}
	}
}

/*
Reset()

Press E to clear the screen and generate a new layout
*/
void Scene0::Reset()
{
	resetCount++;
	std::cout << "Reset Count: " << resetCount << std::endl << std::endl;;
	Scene0RoomManager->ResetValues();
	Scene0RoomManager->GenerateRooms();
	Scene0RoomManager->SetRoomImages();
	ClearScreen();
}

void Scene0::ClearScreen()
{
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
}