#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Engine/Component.h"
#include "Engine/Game.h"

#include "Enemy.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"

class EnemyManager : public Component {
	public:
		EnemyManager(void);
		~EnemyManager(void);

		void createEnemies();
		virtual void onAdd();
		virtual void update();
		void NarrowPhaseDetection(array<Enemy*> _input);
	private:
		array<Enemy*> _enemyList;
};
#endif