#ifndef ENGINE
#define ENGINE

#include "Scene.h"

class Game {
public:
	Game();
	~Game();
	
	static void run();

	static Scene* getCurrentScene();
	static irr::scene::ISceneManager* getSceneManager();
	static void addScene(Scene* defaultScene);
	static void removeScene();
	
	//static Client* client;
	//static Server* server;

	static irr::IrrlichtDevice* device;
	static irr::video::IVideoDriver* driver;

	static irr::gui::IGUIEnvironment* guiEnv;

protected:
	static std::vector<Scene*>* scenes; 
	//static Input inputReceiver;
};

#endif

