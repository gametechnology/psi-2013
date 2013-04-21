#include <Irrlicht\irrlicht.h>
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
	
	void run();

	Scene* getCurrentScene();
	irr::scene::ISceneManager* getSceneManager();
	void addScene(Scene* defaultScene);
	void removeScene();

	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver* driver;
	irr::gui::IGUIEnvironment* guiEnv;

	Entity* game;
	SceneManager* sceneManager;
	static InputManager* input;

protected:
	
};

#endif

