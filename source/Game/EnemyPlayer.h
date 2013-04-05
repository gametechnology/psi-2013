#ifndef ENEMY_PLAYER_H
#define ENEMY_PLAYER_H

#include "Enemy.h"

class EnemyPlayer : public Enemy
{
public:
	EnemyPlayer(irr::core::vector3df position, vector3df speed);
	~EnemyPlayer(void);
private:
};

#endif