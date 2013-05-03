#ifndef LASER_H
#define LASER_H

#include "Engine/Entity.h"
#include "Engine/Game.h"
#include "Enemy.h"
#include "Stations\DefenceStation.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Laser : public Entity
{
	public:
		Laser();
		~Laser();
		
		virtual void init();
		virtual void onAdd();

		void fire(Entity* parent, vector3df target, f32 speed);
		bool isAlive;
		void update();
		void contactResolver(Enemy* input);
		void contactResolver(DefenceStation* input);
	private:
		u32			_timeofLife;
		u32			_currentLife;
		vector3df	_direction;
		unsigned int _damage;
};
#endif