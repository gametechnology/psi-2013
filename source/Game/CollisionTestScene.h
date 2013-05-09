#ifndef CollisionTestScene_h
#define CollisionTestScene_h

#include "Engine\Scene.h"
#include "Stations\Station.h"
#include "Messages.h"

#include "Player.h"
#include "Engine/Camera.h"

// Forward declare Shipmap
class Shipmap;

class CollisionTestScene : public Scene {
public:
	CollisionTestScene();
	virtual ~CollisionTestScene();

	void init();
	void onAdd();
	void update();
private:
	Player* _player;
	Camera* _camera;
};

#endif