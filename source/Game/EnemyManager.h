#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Engine/Component.h"
#include "Engine/Game.h"

#include "Enemy.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"
#include "NetworkInterface.h"

class EnemyManager : public Component, INetworkListener
{
	public:
		EnemyManager(void);
		~EnemyManager(void);

		void createEnemies();
		virtual void onAdd();
		virtual void update();
		void HandleNetworkMessage(NetworkPacket packet);
		void NarrowPhaseDetection(array<Enemy*> _input);
		void LaserNarrowPhase(array<Enemy*> _enput, array<Laser*> _laput);

	private:
		array<Enemy*> _enemyList;
};
#endif