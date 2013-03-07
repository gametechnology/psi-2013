#include "irrlicht.h"
#include "Scene.h"
#include "Message.h"
#include <stack>

#ifndef ENGINE
#define ENGINE

using namespace std;
using namespace irr;

class Engine
{
public:
	Engine(void);
	~Engine(void);
	IrrlichtDevice* device;
	stack<Scene*> scenes; 
	Message* messages;

};

#endif

