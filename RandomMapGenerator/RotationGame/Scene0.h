#ifndef SCENE0_H
#define SCENE0_H

#include "MMath.h"
#include "Scene.h"
#include "Tile.h"
#include "Player.h"
#include "RoomManager.h"
#include <SDL.h>

using namespace MATH;
class Scene0 : public Scene
{
private:
	SDL_Window* window;
	Matrix4 projection;
	SDL_Event Event;

	SDL_Texture* mTexture;
	SDL_Renderer* mRender;
	SDL_Rect* clip;

	RoomManager* Scene0RoomManager;

	int resetCount = 0;

public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &event);

	void Reset();
};

#endif

