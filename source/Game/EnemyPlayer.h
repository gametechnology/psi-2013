#ifndef ENEMY_PLAYER_H
#define ENEMY_PLAYER_H

#include "Enemy.h"

#include <iostream>

class EnemyPlayer : public Enemy
{
public:
	EnemyPlayer(irr::scene::ISceneManager*, irr::core::vector3df position, irr::core::vector3df speed);
	~EnemyPlayer();

	virtual void init();
	void onAdd();	
	virtual void handleMessage(unsigned int, void* data = 0) { };
};

#endif