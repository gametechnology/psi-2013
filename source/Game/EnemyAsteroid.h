#ifndef ENEMY_ASTEROID_H
#define ENEMY_ASTEROID_H

#include "Enemy.h"

class EnemyAsteroid : public Enemy
{
public:
	EnemyAsteroid(irr::core::vector3df position, vector3df velocity);

	void init();
	void onAdd();
	void contactResolverA(Entity* input);
	~EnemyAsteroid(void);
private:
};

#endif
