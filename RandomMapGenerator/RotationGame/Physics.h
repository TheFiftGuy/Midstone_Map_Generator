#ifndef PHYSICS_H
#define PHYSICS_H
#include "Vector.h"
using namespace MATH;
class Physics
{
protected:
	Vec3 pos;
	Vec3 accel;
	Vec3 vel;
	Vec3 force;
	float mass;
public:
	Physics();
	Physics(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);
	~Physics();
	void Update(const float time);
	void ApplyForce(Vec3 force);
	void SetPosition(float posx_, float posy_, float posz_);
	Vec3 GetPosition();
	Vec3 GetVelocity();
	void  SetVelocity(float velx_, float vely_, float velz_);
};
#endif
