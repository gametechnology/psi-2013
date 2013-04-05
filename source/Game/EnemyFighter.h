#ifndef ENEMY_FIGHTER_H
#define ENEMY_FIGHTER_H

#include "Enemy.h"
#include "StateSwitchFighter.h"

class EnemyFighter : public Enemy
{
public:
	EnemyFighter(irr::core::vector3df position);
	~EnemyFighter(void);

	virtual void update();
private:
	StateSwitchFighter* stateSwitch;
};

#endif