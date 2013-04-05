#ifndef LASER_H
#define LASER_H

#include "Engine/Entity.h"
#include "Engine/Game.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Laser : public Entity
{
	public:
		Laser();
		~Laser();
		void fire(Entity* parent, vector3df target, f32 speed);
		bool isAlive;
		void update();
	private:
		u32			_timeofLife;
		u32			_currentLife;
		vector3df	_direction;
};
#endif