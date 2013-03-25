#pragma once
#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"
class Thruster : public Component
{
public:
	Thruster(Entity *parent, vector3df position, vector3df initialDirection);
	~Thruster(void);
	void Activate();

private:
	void update();
	float force_;
	vector3df position_;
	vector3df distanceFromCenter_;
	vector3df direction_;
	Entity * parent_;
	
	vector3df directionalForce_;
	vector3df angularForce_;
};

