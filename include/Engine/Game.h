#include "Irrlicht\irrlicht.h"
#include "Engine\Scene.h"
#include "Engine\Client.h"
#include "Engine\Server.h"
#include "Engine\Input.h"
#include <vector>

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
	
	static Client* client;
	static Server* server;

	static IrrlichtDevice* device;
	static IVideoDriver* driver;

	static IGUIEnvironment* guiEnv;
protected:
	static std::vector<Scene*>* scenes; 
	static Input inputReceiver;
};

#endif

