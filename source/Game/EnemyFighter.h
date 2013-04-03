#ifndef ENEMY_FIGHTER_H
#define ENEMY_FIGHTER_H

#include "Enemy.h"

class EnemyFighter : public Enemy
{
public:
	EnemyFighter(irr::core::vector3df position);
	~EnemyFighter(void);
};

#endif