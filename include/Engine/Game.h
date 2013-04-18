#ifndef ENGINE
#define ENGINE

#include "Irrlicht\irrlicht.h"
#include "Scene.h"
#include "SceneManager.h"

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

protected:
	std::vector<Scene*>* scenes;
	//Input inputReceiver;
};

#endif

