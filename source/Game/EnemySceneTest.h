#ifndef ENEMY_SCENE_TEST_H
#define ENEMY_SCENE_TEST_H

#include "Engine\Scene.h"
#include "NetworkInterface.h"
#include "Enemy.h"
#include "EnemyAsteroid.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"

class EnemySceneTest :
	public Scene, public INetworkListener
{
public:
	EnemySceneTest(void);
	~EnemySceneTest(void);
	virtual void init();
	virtual void update();
	void createEnemies();

	void HandleNetworkMessage(NetworkPacket packet);

	ISceneManager* smgr;
	ICameraSceneNode* camera;
	ILightSceneNode* light;

private:
	array<Enemy*> _enemyList;
};

#endif