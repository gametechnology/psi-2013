#ifndef ENEMY_ASTEROID_H
#define ENEMY_ASTEROID_H

#include "Enemy.h"

class EnemyAsteroid : public Enemy
{
public:
	EnemyAsteroid(irr::core::vector3df _position);
	virtual void lupdate(Enemy* enemy,vector3df speed);
	virtual void update();
	~EnemyAsteroid(void);
private:
	vector3df speed;
	unsigned int acceleration;
};

#endif
