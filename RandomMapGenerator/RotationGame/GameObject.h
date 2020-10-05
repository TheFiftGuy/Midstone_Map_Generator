#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>


class GameObject
{
public:
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents(const SDL_Event &event) = 0;

};

#endif