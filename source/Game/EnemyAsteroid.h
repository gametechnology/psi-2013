#ifndef ENEMY_ASTEROID_H
#define ENEMY_ASTEROID_H

#include "Enemy.h"

class EnemyAsteroid : public Enemy
{
public:
	EnemyAsteroid(irr::core::vector3df position);
	void linearpath(vector3df speed);
	~EnemyAsteroid(void);
private:
	vector3df speed;
	unsigned int acceleration;
};

#endif
