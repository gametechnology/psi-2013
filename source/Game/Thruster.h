#pragma once
#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"
class Thruster : public Entity
{
public:
	Thruster(Composite *parent, vector3df position, vector3df initialDirection, matrix4* inertiaMatrix);
	~Thruster(void);
	void Activate();

	//when the ship rotates, the direction (in world space) the thruster pushes also changes
	vector3df UpdateDirection();

	vector3df pushDirection();
private:
	float _force;
	
};

