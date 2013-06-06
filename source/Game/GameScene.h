#ifndef GAMESCENE
#define GAMESCENE

#include <Engine\Network.h>
#include <Engine\NetworkPacket.h>
#include <Engine\INetworkListener.h>
#include <Engine\Scene.h>
#include <Engine\Camera.h>

#include "Ship.h"
#include "ShipMover.h"
#include "BasicMoverComponent.h"
#include "Stations\Station.h"
#include "Laser.h"
#include "ObjectPool.h"
#include "NetworkInterface.h"
#include "PlayerManager.h"

// Forward declare Shipmap
class Shipmap;

class GameScene : public Scene, INetworkListener {
public:
	GameScene(std::list<Player*>, bool isTestMap = false);
	virtual ~GameScene();

	void init();
	void onAdd();
	void update();
	void switchStation(StationType type);
	void HandleNetworkMessage(NetworkPacket packet);
private:
	bool testMap;
	Camera *_camera;
	Shipmap* _shipmap;
	int _sendLasersTimer;
	ObjectPool<Laser>* _laserPool;
	Ship* _ship;
	Ship* _shipEnemy;

	std::list<Player*> _playerList;
};

#endif