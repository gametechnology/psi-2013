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
	Camera *_camera;
	Shipmap* _shipmap;
	Ship* _ship;
	Ship* _shipEnemy;

	std::list<Player*> _playerList;
};

#endif