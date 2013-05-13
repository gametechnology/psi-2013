#ifndef CollisionTestScene_h
#define CollisionTestScene_h

#include "Engine\Scene.h"
#include "Engine\Camera.h"
#include "Stations\Station.h"
#include "ENgine\InputManager.h"
#include "Messages.h"
#include "NetworkInterface.h"


#include "Enemy.h"
#include "EnemyPlayer.h"
#include "EnemyAsteroid.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "Player.h"
#include "Ship.h"

// Forward declare Shipmap
class Shipmap;

class CollisionTestScene : public Scene {
public:
	CollisionTestScene(void);
	virtual ~CollisionTestScene(void);

	//functions from Scene
	void init();
	void onAdd();
	void update();
	void HandleNetworkMessage(NetworkPacket packet);

private:
	//create an enemylist
	vector<Enemy*> _enemyList;

	void createTestEnemies();
	void createLaserTestObjects();
	void createBulletTestObjects();
	void createLaserToBullet();
	void createRemoveEnemyTest();
	void createLaserAndShip();

	bool removeenemytestinitiationcheck;

	Ship* _ship;
};

#endif