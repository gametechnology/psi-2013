#ifndef GAMESCENE
#define GAMESCENE

#include <Engine\Network.h>
#include <Engine\NetworkPacket.h>
#include <Engine\INetworkListener.h>
#include <Engine\Scene.h>
#include <Engine\Camera.h>

#include "Ship.h"
#include "RemoteShip.h"
#include "ShipMover.h"
#include "BasicMoverComponent.h"
#include "Stations\Station.h"

// Forward declare Shipmap
class Shipmap;

class GameScene : public Scene, public INetworkListener {
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

	Shipmap* _shipmap;
	Camera* _player;
	Ship* _ship;
	RemoteShip* _ship2;

	std::list<Player*> _playerList;
};

#endif