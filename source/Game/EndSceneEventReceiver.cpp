#include "EndSceneEventReceiver.h"

using namespace irr;
using namespace irr::gui;

EndSceneEventReceiver::EndSceneEventReceiver(SAppContext& context) : _context(context)
{
}

bool EndSceneEventReceiver::OnEvent(const SEvent& event)
{
	if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{
		case 0:
			_context.u_interface->resetInterface();
			_context.core->setActiveScene(new MainMenuScene(_context.core, _context.u_interface));
			break;
		}
	}
	return false;
}