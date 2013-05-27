#ifndef ENEMY_PLAYER_H
#define ENEMY_PLAYER_H

#include "Enemy.h"

#include <iostream>

class EnemyPlayer : public Enemy
{
public:
	EnemyPlayer(irr::scene::ISceneManager*, irr::core::vector3df position, irr::core::vector3df speed);
	~EnemyPlayer();

	void init();
	void onAdd();	
};

#endif