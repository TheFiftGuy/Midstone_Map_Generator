#include "Physics.h"
#include <iostream>


Physics::Physics()
{
	Physics(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), float(1.0f));
}


Physics::~Physics()
{
}

Physics::Physics(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_) {
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;

	mass = mass_;
}

void Physics::Update(const float time) {
	//printf("%.3f      %.3f  %.3f   %.3f\n", pos.x, vel.x, accel.x, force.x);
	pos.x += vel.x * time + 0.5f * accel.x * time * time;
	vel.x += accel.x * time;
	pos.y += vel.y * time + 0.5f * accel.y * time * time;
	vel.y += accel.y * time;
	pos.z += vel.z * time + 0.5f * accel.z * time * time;
	vel.z += accel.z * time;
}

void Physics::ApplyForce(Vec3 force_) {
	force = force_; //gets force to be referenced in print statement
	accel.x = force.x / mass;
	accel.y = force.y / mass;
	accel.z = force.z / mass;

}
void Physics::SetPosition(float posx_, float posy_, float posz_)
{
	pos.x = posx_;
	pos.y = posy_;
	pos.z = posz_;
}
Vec3 Physics::GetPosition() {
	return pos;
}
void Physics::SetVelocity(float velx_, float vely_, float velz_)
{
	vel.x = velx_;
	vel.y = vely_;
	vel.z = velz_;
}
Vec3 Physics::GetVelocity() {
	return vel;
}
