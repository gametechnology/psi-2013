#ifndef END_SCENE_EVENT_RECEIVER_H
#define END_SCENE_EVENT_RECEIVER_H

#include <Irrlicht\irrlicht.h>
#include <Engine\Core.h>
#include <Engine\Scene.h>
#include <Engine\Interface.h>

#include "MainMenuScene.h"

struct EndAppContext
{
	Core* core;
	irr::s32 counter;
	Interface* u_interface;
};

enum InterfaceElements
{
	END_GAME_WINDOW = 0,
	WIN_LOSE_MESSAGE,
	BACK_BUTTON
};

class EndSceneEventReceiver : public irr::IEventReceiver
{
public:
	EndSceneEventReceiver(EndAppContext& context);

	virtual bool OnEvent(const irr::SEvent& event);
private:
	EndAppContext& _context;
};

#endif