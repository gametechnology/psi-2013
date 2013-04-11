#include "Scene.h"

#include <Irrlicht\irrlicht.h>
#include <forward_list>
#include <Engine\Input.h>

#ifndef ENGINE
#define ENGINE

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

class Game
{
public:
	Game();
	~Game();
	
	static void run();

	static Scene* getCurrentScene();
	static ISceneManager* getSceneManager();
	static void addScene(Scene* defaultScene);
	static void removeScene();

	static IrrlichtDevice* device;
	static IVideoDriver* driver;

	static IGUIEnvironment* guiEnv;
protected:
	static std::forward_list<Scene*>* scenes; 
	static Input inputReceiver;
};

#endif

