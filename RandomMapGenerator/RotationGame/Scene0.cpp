#include "Scene0.h"
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>

Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	playerSprite = nullptr;
	mRender = nullptr;
	
}

Scene0::~Scene0(){
}

bool Scene0::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, 200.0f, 0.0f, 100.0f,0.0f,1.0f);
	projection =  ndc * ortho;

	playerSprite = new Player(Vec3(100.0f, 50.0f, 0.0f), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 100.0);
	playerSprite->thePlayer = IMG_Load("test.png");
	

	tile = new Tile(Vec3(15.0f, 90.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 100, 100);			// adding Map to OnCreate with position
	tile->image = SDL_LoadBMP("mapone.bmp");

	tile2 = new Tile(Vec3(90.0f, 90.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 5, 5);
	tile2->image = IMG_Load("test.png");

	if (tile->image == nullptr) {
		return false;
	}

	
	return true;
}

void Scene0::OnDestroy() {
	delete tile;
}

void Scene0::Update(const float time) {
	
		
		playerSprite->Update(time);
		playerSprite->CheckCollisions(*tile2);
}

void Scene0::Render() {
	
	Vec3 screenCoords = projection * tile->GetPosition();
	Vec3 screenCoords3 = projection * tile2->GetPosition();
	
	SDL_Rect rect;
	SDL_Rect rect2;
	//SDL_Rect rect2;
	rect.h = tile->image->h;
	rect.w = tile->image->w;
	rect.x = screenCoords.x; 
	rect.y = screenCoords.y; 

	rect2.h = tile2->image->h;
	rect2.w = tile2->image->w;
	rect2.x = screenCoords3.x;
	rect2.y = screenCoords3.y;
	if (clip != NULL)
	{
		rect.w = clip->w;
		rect.h = clip->h;
	}
	Vec3 screenCoords2 = projection * playerSprite->GetPosition();
	SDL_Rect spritePosition;
	spritePosition.h = playerSprite->thePlayer->h;
	spritePosition.w = playerSprite->thePlayer->w;
	spritePosition.x = screenCoords2.x;
	spritePosition.y = screenCoords2.y;

	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255.0f,255.0f,255.0f));		//changed color to white from blue.
	SDL_BlitSurface(tile->image, nullptr, screenSurface, &rect);
	SDL_BlitSurface(tile2->image, nullptr, screenSurface, &rect2);
	SDL_RenderCopyEx(mRender, mTexture, clip, &rect,playerSprite->degrees1 , NULL, SDL_FLIP_NONE);
	SDL_BlitSurface(playerSprite->thePlayer, NULL, screenSurface, &spritePosition);
	SDL_RenderPresent(mRender);
	SDL_UpdateWindowSurface(window);



}

void Scene0::HandleEvents(const SDL_Event & event)
{
	playerSprite->HandleEvents(event);
}