#include "..\Irrlicht\irrlicht.h"
#include "Scene.h"
#include <forward_list>
#include "Input.h"

#ifndef ENGINE
#define ENGINE

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

static Input eventReceiver;

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
	
protected:
	static std::forward_list<Scene*>* scenes; 
};

#endif

