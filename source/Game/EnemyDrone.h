#ifndef ENEMY_DRONE_H
#define ENEMY_DRONE_H

#include "Enemy.h"

class EnemyDrone : public Enemy
{
	public:
		EnemyDrone(irr::core::vector3df position);
		EnemyDrone(unsigned int health); 
		~EnemyDrone(void);
	private:
};

#endif