#ifndef ENEMY_PLAYER_H
#define ENEMY_PLAYER_H

#include "Enemy.h"

class EnemyPlayer : public Enemy
{
public:
	EnemyPlayer(irr::core::vector3df position, vector3df speed);
	void init();
	void onAdd();
	~EnemyPlayer(void);
private:
};

#endif