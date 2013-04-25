#pragma once
#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"
class Thruster : public Component
{
public:
	Thruster(Composite *parent, irr::core::vector3df position, irr::core::vector3df initialDirection);
	~Thruster(void);
	void Activate();

	//when the ship rotates, the direction (in world space) the thruster pushes also changes
	irr::core::vector3df UpdateDirection();

	irr::core::vector3df pushDirection();
private:
	float _force;
	
};

