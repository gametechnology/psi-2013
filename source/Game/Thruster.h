#pragma once
#include "Engine\Game.h"
#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"
class Thruster : public Entity
{
public:
	Thruster(Composite *parent, irr::core::vector3df position, irr::core::vector3df initialDirection);
	virtual ~Thruster();
	void Activate();
	void init();
	void draw();
	void update();
	void handleMessage(unsigned int message, void* data);

	void printAng();
	irr::core::vector3df UpdateDirection();
	float force_;

	vector3df position;
	vector3df nPosition;
	vector3df direction;
	vector3df nDirection;

	vector3df forceComponent1;
	vector3df forceComponent2;

	vector3df linearForce;
	vector3df angularForce;
	Entity * parent;
	vector3df torque;

	irr::core::vector3df pushDirection();

};

