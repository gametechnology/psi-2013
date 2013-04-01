#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Engine/Entity.h"
#include "Engine/Game.h"
#include "Enemy.h"


class EnemyManager : public Entity
{
	public:
		EnemyManager(void);
		~EnemyManager(void);
		void createEnemies();
		void createFighters();
		void createKamikazes();

	private:
		array<Enemy>	_enemies;
		float			_posX;
		float			_posY;
		float			_posZ;
};
#endif