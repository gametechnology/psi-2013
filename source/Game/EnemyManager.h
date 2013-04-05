#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Engine/Entity.h"
#include "Engine/Game.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"


class EnemyManager : public Scene
{
	public:
		EnemyManager(void);
		~EnemyManager(void);
		void createEnemies();
		virtual void update();

	private:
		array<EnemyDrone>_enemydrones;
		array<EnemyFighter>_enemyfighters;
		array<EnemyAsteroid>_enemyasteroids;
};
#endif