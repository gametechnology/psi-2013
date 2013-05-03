#ifndef ENEMY_SCENE_TEST_H
#define ENEMY_SCENE_TEST_H

#include "Engine\Scene.h"
#include "NetworkInterface.h"
#include "Enemy.h"
#include "Irrlicht\ICameraSceneNode.h"
#include "Irrlicht\ILightSceneNode.h"
#include "EnemyAsteroid.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"

class EnemySceneTest :
	public Scene, public INetworkListener
{
public:
	EnemySceneTest(void);
	~EnemySceneTest(void);
	void init();
	void update();
	void onAdd();
	void createEnemies();

	void HandleNetworkMessage(NetworkPacket packet);

	irr::scene::ICameraSceneNode* camera;
	irr::scene::ILightSceneNode* light;

private:
	array<Enemy*> _enemyList;
};

#endif