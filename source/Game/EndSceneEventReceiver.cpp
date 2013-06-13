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
			system("\"C:\\Users\\SamanthaVosh\\Desktop\\School\\Jaar_3\\Project_Stella_Incognita\\Sprint_2\\psi-2013\\psi-2013\\psi-2013\\binProject Stella Incognita.exe\"");
			std::exit(0);
			break;
		}
	}
	return false;
}