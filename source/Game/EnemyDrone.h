#ifndef ENEMY_DRONE_H
#define ENEMY_DRONE_H

#include "Enemy.h"
#include "StateSwitchDrone.h"

class EnemyDrone : public Enemy
{
public:
	EnemyDrone(irr::core::vector3df position);
	EnemyDrone(unsigned int health); 
	~EnemyDrone(void);

	virtual void update();
private:

	StateSwitchDrone* stateSwitch;
};

#endif