#ifndef GAMESCENE
#define GAMESCENE

#include "Engine\Scene.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	void init();
	void onAdd();
	void update();
};

#endif