#include "irrlicht.h"
#include "Scene.h"
#include "Message.h"
#include <stack>

#ifndef ENGINE
#define ENGINE

using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

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
	static Message* messages;
protected:
	static stack<Scene*>* scenes; 
};

#endif

