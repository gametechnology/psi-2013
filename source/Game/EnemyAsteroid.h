#ifndef ENEMY_ASTEROID_H
#define ENEMY_ASTEROID_H

#include "Enemy.h"
#include <Engine/GameObject.h>
#include <Engine/CollisionSystem.h>
#include <iostream>

class EnemyAsteroid : public Enemy
{
public:
	EnemyAsteroid(irr::scene::ISceneManager*, irr::core::vector3df position, irr::core::vector3df velocity);
	~EnemyAsteroid();
	
	virtual void init();
	void onAdd();
	virtual void handleMessage(unsigned int, void* data = 0) { };
};

#endif
