#ifndef ROTATABLEOBJECT_H
#define ROTATABLEOBJECT_H
#include "GameObject.h"
#include <SDL.h>
#include "Vector.h"
#include "VMath.h"
#include "Physics.h"

using namespace MATH;

class RotatableObject: public GameObject, public Physics
{
public:
	int height;
	int width;
	RotatableObject();
	~RotatableObject();
	RotatableObject(Vec3 pos_, Vec3 vel_, Vec3 accel_, int width_, int height_);
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render()const;
	void HandleEvents(const SDL_Event& event);

};

#endif

