#ifndef END_SCENE_EVENT_RECEIVER_H
#define END_SCENE_EVENT_RECEIVER_H

#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"
#include "Engine\Scene.h"

// irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// standard namespace
using namespace std;

class EndSceneEventReceiver : public IEventReceiver
{
public:
	EndSceneEventReceiver(Game* game);

	virtual bool OnEvent(const SEvent& event);

private:
	Game* _contextGame;
};

#endif