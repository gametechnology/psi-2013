#ifndef ENEMY_DRONE_H
#define ENEMY_DRONE_H

#include "Enemy.h"
#include "StateSwitchDrone.h"

#include <Engine/GameObject.h>

class EnemyDrone : public Enemy
{
public:
	EnemyDrone(irr::scene::ISceneManager*, irr::core::vector3df position);
	EnemyDrone(unsigned int health); 
	~EnemyDrone(void);

	virtual void init();
	void onAdd();
	virtual void handleMessage(unsigned int, void* data = 0) { };

	virtual void chase(irr::core::vector3df target);
	virtual void update();
	virtual void wander();
private:	
	StateSwitchDrone* stateSwitch;
};

#endif