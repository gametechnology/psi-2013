#ifndef GAMESCENE
#define GAMESCENE

#include <Engine\Network.h>
#include <Engine\NetworkPacket.h>
#include <Engine\INetworkListener.h>
#include <Engine\Scene.h>
#include <Engine\Camera.h>

#include "ShipInterface.h"
#include "Ship.h"
#include "ProxyShip.h"
#include "ShipMover.h"
#include "BasicMoverComponent.h"
#include "Stations\Station.h"
#include "Laser.h"
#include "ObjectPool.h"
#include "NetworkInterface.h"
#include "PlayerManager.h"
#include "MapGenerator.h"

// Forward declare Shipmap
class Shipmap;

class GameScene : public Scene, INetworkListener, IShipListener {
public:
	GameScene(std::list<Player*>, bool isTestMap = false);
	virtual ~GameScene();

	void init();
	void onAdd();
	void update();
	void HandleNetworkMessage(NetworkPacket packet);

	void handleShipMessage(ShipMessage message);
	Shipmap* getShipMap();
private:
	bool testMap;
	Camera *_camera;
	Shipmap* _shipmap;
	int _sendLasersTimer;
	ObjectPool<Laser>* _laserPool;
	ShipInterface* _ship;
	ShipInterface* _shipEnemy;
	GalaxyMap* galaxyMap;

	std::list<Player*> _playerList;
};

#endif