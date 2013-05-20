#ifndef GAMESCENE
#define GAMESCENE

#include "Engine\Scene.h"
#include "Stations\Station.h"
#include "Laser.h"
#include "ObjectPool.h"
#include "NetworkInterface.h"

// Forward declare Shipmap
class Shipmap;

class GameScene : public Scene, INetworkListener {
public:
	GameScene();
	virtual ~GameScene();

	void init();
	void onAdd();
	void update();
	void switchStation(StationType type);
	void HandleNetworkMessage(NetworkPacket packet);
private:
	Shipmap* _shipmap;
	int _sendLasersTimer;
	ObjectPool<Laser>* _laserPool;
};

#endif