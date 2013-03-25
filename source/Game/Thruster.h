#pragma once
#include "Engine\Game.h"
#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"
class Thruster : public Entity
{
public:
	Thruster(Composite* parent, vector3df position, vector3df initialDirection);
	virtual ~Thruster();
	void Activate();
	void init();
	void draw();
	void update();
	void handleMessage(unsigned int message, void* data);
private:
	float force_;
	vector3df position_;
	vector3df distanceFromCenter_;
	vector3df direction_;
	Entity * parent_;
	
	vector3df directionalForce_;
	vector3df angularForce_;
};

