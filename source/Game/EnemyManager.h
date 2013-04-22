#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Engine/Entity.h"
#include "Engine/Game.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"
#include "NetworkInterface.h"


class EnemyManager : public Scene, INetworkListener
{
	public:
		EnemyManager(void);
		~EnemyManager(void);
		void createEnemies();
		virtual void update();
		void HandleNetworkMessage(NetworkPacket packet);
	//	void BroadPhaseDetection();
		void NarrowPhaseDetection(array<Enemy*> _input);

	private:
		array<Enemy*> _enemyList;
};
#endif