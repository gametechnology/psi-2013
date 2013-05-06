#ifndef GAMESCENE
#define GAMESCENE

#include "Engine\Scene.h"
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
};

#endif