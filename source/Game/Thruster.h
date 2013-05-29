#ifndef THRUSTER
#define THRUSTER

#include <Engine/Core.h>
#include <Engine\GameObject.h>
#include <Irrlicht/irrlicht.h>

#include <iostream>

class Thruster : public GameObject
{
public:
	Thruster(irr::core::vector3df position, irr::core::vector3df initialDirection);
	virtual ~Thruster();
	void Activate();
	void init();
	void draw();
	void update();
	void handleMessage(unsigned int message, void* data);

	void printAng();
	irr::core::vector3df UpdateDirection();

	irr::core::vector3df nPosition;
	irr::core::vector3df direction;
	irr::core::vector3df nDirection;

	irr::core::vector3df forceComponent1;
	irr::core::vector3df forceComponent2;

	irr::core::vector3df linearForce;
	irr::core::vector3df angularForce;
	GameObject* parent;
	irr::core::vector3df torque;

	irr::core::vector3df pushDirection();
};

#endif

