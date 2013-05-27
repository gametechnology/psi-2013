#ifndef ENGINE
#define ENGINE

#include "Irrlicht\irrlicht.h"
#include "Engine\Scene.h"
#include "Engine\SceneManager.h"
#include "Engine\InputManager.h"
#include "Engine\CollisionSystem.h"

class Entity;

class Game {
public:
	Game();
	~Game();
	
	void init();
	void run();

	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver* driver;
	irr::gui::IGUIEnvironment* guiEnv;

	Entity* game;
	SceneManager* sceneManager;
	InputManager* input;
	static CollisionSystem* collisionSystem;

protected:
	
};

#endif

