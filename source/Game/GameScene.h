#ifndef GAMESCENE
#define GAMESCENE

#include "Engine\Scene.h"
#include "Stations\Station.h"

// Forward declare Shipmap
class Shipmap;

class GameScene : public Scene {
public:
	GameScene(bool isTestMap = false);
	virtual ~GameScene();

	void init();
	void onAdd();
	void update();
	void switchStation(StationType type);
private:
	bool testMap;

	Shipmap* _shipmap;
};

#endif