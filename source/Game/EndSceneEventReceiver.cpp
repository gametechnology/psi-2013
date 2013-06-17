#include "EndSceneEventReceiver.h"

EndSceneEventReceiver::EndSceneEventReceiver(Game* game)
{
	this->_contextGame = game;
}

bool EndSceneEventReceiver::OnEvent(const SEvent& event)
{
	if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{
		case 0:
			this->_contextGame->guiEnv->clear();
			this->_contextGame->sceneManager->activateScene("MainMenuScene");
			this->_contextGame->sceneManager->destroyScene("EndScene");
			break;
		}
	}
	return false;
}