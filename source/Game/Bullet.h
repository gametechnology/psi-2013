#pragma once
#include "Engine\Game.h"

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(Composite* parent, vector3df start, vector3df end, f32 speed);
	~Bullet();

	void update();
	void setState(Composite* parent, vector3df start, vector3df end, f32 speed);
private:
	u32 _currentFlightTime;
	u32 _maxFlightTime;
};