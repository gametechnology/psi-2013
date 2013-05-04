#ifndef GAMESCENE
#define GAMESCENE

#include "Engine\Scene.h"
#include "Engine\Camera.h"
#include "Ship.h"
#include "ShipMover.h"
#include "BasicMoverComponent.h"
#include "Stations\Station.h"

// Forward declare Shipmap
class Shipmap;

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	void init();
	void onAdd();
	void update();
	void switchStation(StationType type);
private:
	Shipmap* _shipmap;
private:
	Camera* _player;
	Ship* _ship;
	Ship* _ship2;
};

#endif