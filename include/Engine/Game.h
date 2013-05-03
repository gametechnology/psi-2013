#ifndef ENGINE
#define ENGINE

#include "Irrlicht\irrlicht.h"
#include "Engine\Scene.h"
#include "Engine\SceneManager.h"
#include "Engine\InputManager.h"

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

protected:
	
};

#endif

