#include "RotatableObject.h"

RotatableObject::RotatableObject()
{

}

RotatableObject::~RotatableObject()
{
}

RotatableObject::RotatableObject(Vec3 pos_, Vec3 vel_, Vec3 accel_, int width_, int height_)
{
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;

	width = width_;
	height = height_;
}

bool RotatableObject::OnCreate()
{
	return false;
}

void RotatableObject::OnDestroy()
{
}

void RotatableObject::Update(const float deltaTime)
{
	
}

void RotatableObject::Render() const
{
}

void RotatableObject::HandleEvents(const SDL_Event& event)
{
	
}

