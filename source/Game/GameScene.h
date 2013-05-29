#ifndef GAMESCENE
#define GAMESCENE

#include <Engine/Interface.h>
#include <Engine\Network.h>
#include <Engine\NetworkPacket.h>
#include <Engine\INetworkListener.h>
#include <Engine\Scene.h>
#include <Engine\CameraComponent.h>

#include "Ship.h"
#include "ShipMover.h"
#include "BasicMoverComponent.h"
#include "Stations\Station.h"
#include "Laser.h"
#include "ObjectPool.h"
#include "NetworkInterface.h"

#include "MapGenerator.h"
#include "SectorManager.h"
#include "Shipmap.h"
#include "SendAndReceivePackets.h"

// Forward declare Shipmap
class Shipmap;

class GameScene : public Scene, INetworkListener {
public:
	GameScene(Core*, Interface*, std::list<Player*>, bool isTestMap = false);
	virtual ~GameScene();

	virtual void init();
	virtual void update();
	virtual void draw();

	virtual void requestNextScene();
	virtual void requestPreviousScene();

	virtual void notify(void* data);

	void switchStation(StationType type);
	void handleNetworkMessage(NetworkPacket packet);
private:
	Core* _core;
	Interface* _interface;

	bool testMap;
	CameraComponent *_camera;
	Shipmap* _shipmap;
	int _sendLasersTimer;
	ObjectPool<Laser>* _laserPool;
	Ship* _ship;
	Ship* _shipEnemy;

	std::list<Player*> _playerList;
};

#endif