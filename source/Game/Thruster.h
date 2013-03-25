#pragma once
#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"
class Thruster : public Component
{
public:
	Thruster(Composite *parent, vector3df position, vector3df initialDirection);
	~Thruster(void);
	void Activate();

	//when the ship rotates, the direction (in world space) the thruster pushes also changes
	vector3df UpdateDirection();

	vector3df pushDirection();
private:
	float _force;
	
};

