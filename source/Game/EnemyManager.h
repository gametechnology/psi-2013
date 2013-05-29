#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <Engine/Composite.h>

#include "Enemy.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyPlayer.h"
#include "EnemyAsteroid.h"
#include "NetworkInterface.h"


class EnemyManager : public Composite
{
	public:
		EnemyManager(irr::scene::ISceneManager*);
		~EnemyManager();

		void createEnemies();
		
		virtual void init();
		virtual void update();

		void narrowPhaseDetection(std::list<Component*> _input);
		void laserNarrowPhase(std::list<Component*> _input, std::list<Laser*> _laput);

		irr::core::vector3df* createBoundingBox(Enemy* object);
	private:
		Enemy* player;
		irr::scene::ISceneManager* _smgr;
};
#endif