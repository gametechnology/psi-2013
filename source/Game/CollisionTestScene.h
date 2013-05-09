#ifndef CollisionTestScene_h
#define CollisionTestScene_h

#include "Engine\Scene.h"
#include "Engine\Camera.h"
#include "Stations\Station.h"
#include "Messages.h"
#include "NetworkInterface.h"


#include "Enemy.h"
#include "EnemyPlayer.h"
#include "EnemyAsteroid.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "Player.h"

// Forward declare Shipmap
class Shipmap;

class CollisionTestScene : public Scene {
public:
	CollisionTestScene(void);
	virtual ~CollisionTestScene(void);

	void init();
	void onAdd();
	void update();
	void createTestEnemies();
	void HandleNetworkMessage(NetworkPacket packet);

private:
	Player* _player;
	Camera* _camera;
	vector<Enemy*> _enemyList;
	
	//Visual testing with camera and light
	//irr::scene::ILightSceneNode*	_light;

	//add two players for testing
	EnemyPlayer* _player1;
	EnemyPlayer* _player2;
};

#endif