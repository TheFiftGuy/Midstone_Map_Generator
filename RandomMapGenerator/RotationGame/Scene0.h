#ifndef SCENE0_H
#define SCENE0_H

#include "MMath.h"
#include "Scene.h"
#include "Tile.h"
#include "Player.h"
#include <SDL.h>

using namespace MATH;
class Scene0 : public Scene {
private:
	SDL_Window* window;
	Matrix4 projection;
	float timePassed = 0.0f;
	int i = 0;
	SDL_Event Event;
	Tile* tile;
	Tile* tile2;
	//Player player;
	class Player* playerSprite;

	SDL_Texture* mTexture;
	SDL_Renderer* mRender;
	SDL_Rect* clip;

	
public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &event);
};

#endif

