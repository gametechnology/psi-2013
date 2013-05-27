#ifndef ENEMY_FIGHTER_H
#define ENEMY_FIGHTER_H

#include "Enemy.h"
#include "StateSwitchFighter.h"
#include "ObjectPool.h"
#include "Laser.h"

#include <Engine/GameObject.h>

class EnemyFighter : public Enemy
{
public:
	EnemyFighter(irr::scene::ISceneManager*, irr::core::vector3df position);
	~EnemyFighter(void);

	void SetTarget(irr::core::vector3df target);
	virtual void chase(irr::core::vector3df target);
	void fireLaserAt(irr::core::vector3df target);
	
	virtual void init();
	virtual void onAdd();
	virtual void update();

	static ObjectPool<Laser>* laserPool;
private:
	int	_fireTime;
	irr::core::vector3df	_target;
	irr::core::vector3df	_endPosition;
	StateSwitchFighter* stateSwitch;
};

#endif