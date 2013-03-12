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
	void run();
	static Scene getTopScene();
	static void addScene(Scene* defaultScene);

	static IrrlichtDevice* device;
	static IVideoDriver* driver;
	static stack<Scene*>* scenes; 
	static Message* messages;

};

#endif

