#ifndef ENEMY_FIGHTER_H
#define ENEMY_FIGHTER_H

#include "Enemy.h"
#include "StateSwitchFighter.h"
#include "ObjectPool.h"
#include "Laser.h"

class EnemyFighter : public Enemy
{
public:
	EnemyFighter(irr::core::vector3df position);
	~EnemyFighter(void);

	void SetTarget(vector3df target);
	virtual void chase(vector3df target);
	void fireLaserAt(vector3df target);
	
	virtual void init();
	virtual void onAdd();
	virtual void update();

	static ObjectPool<Laser>* laserPool;
private:
	int			_fireTime;
	vector3df	_target;
	vector3df	_endPosition;
	StateSwitchFighter* stateSwitch;
};

#endif