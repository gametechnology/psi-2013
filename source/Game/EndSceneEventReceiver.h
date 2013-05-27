#ifndef END_SCENE_EVENT_RECEIVER_H
#define END_SCENE_EVENT_RECEIVER_H

#include <Irrlicht\irrlicht.h>
#include <Engine\Core.h>
#include <Engine\Scene.h>
#include <Engine\Interface.h>

#include "MainMenuScene.h"

struct SAppContext
{
	Core* core;
	irr::s32 counter;
	Interface* u_interface;
};

class EndSceneEventReceiver : public IEventReceiver
{
public:
	EndSceneEventReceiver(SAppContext& context);

	virtual bool OnEvent(const SEvent& event);
private:
	SAppContext& _context;
};

#endif