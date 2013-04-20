#include "MainMenuEventReceiver.h"
#include "MainMenuScene.h"
#include "Engine\Network.h"

MainMenuEventReceiver::MainMenuEventReceiver(SAppContext & context) : Context(context)
{
}

bool MainMenuEventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();
        IGUIEnvironment* env = Game::device->getGUIEnvironment();
		MainMenuScene* mainmenu = ((MainMenuScene*)Game::getCurrentScene());
		char* ipadress;
		 wchar_t* inputwchar;
		 Player* newplayer;
		 NetworkPacket packet(START_GAME);
        switch(event.GUIEvent.EventType)
        { 
				case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case 1:
					inputwchar = (wchar_t*)mainmenu->Ipadresinput->getText();
					ipadress = (char*)malloc(wcslen(inputwchar)+ 1);
					wcstombs(ipadress, inputwchar, wcslen(inputwchar));
					ipadress[wcslen(inputwchar)] = 0;
					if(*ipadress == ' ' || *ipadress == NULL){
						mainmenu->messagebox =  Game::guiEnv->addMessageBox(L"Messsage",L"Fill in an Ipadress",true,1,mainmenu->mainMenuWindow);
						mainmenu->messagebox->setDraggable(false);
					}else{
						Network::GetInstance()->InitializeClient(ipadress);
						if(!Network::GetInstance()->IsConnected()){
							mainmenu->messagebox =  Game::guiEnv->addMessageBox(L"Messsage",L"Not able to connect to server",true,1,mainmenu->mainMenuWindow);
							mainmenu->messagebox->setDraggable(false);
						}else{
							mainmenu->createServerWindow_Button->setVisible(false);
							mainmenu->joinServerWindow_Button->setVisible(false);
							mainmenu->Clientlist->setVisible(true);
							mainmenu->Ipadresinput->setVisible(false);
							Game::guiEnv->addStaticText(L"Waiting for host to start the game",rect<s32>(position2di(300,165),dimension2di(200,25)),false,true,mainmenu->mainMenuWindow);
						}

						
						
					}
						
					
					return true;
				case 2:
					Network::GetInstance()->InitializeServer();
					mainmenu->createServerWindow_Button->setVisible(false);
					mainmenu->joinServerWindow_Button->setVisible(false);
					mainmenu->Ipadresinput->setVisible(false);
					mainmenu->start_button->setVisible(true);
					mainmenu->Clientlist->setVisible(true);
					newplayer = new Player(NULL);
					newplayer->Name = L"Player";
					newplayer->Team = 1;
					mainmenu->playerlist.push_back(newplayer);
					return true;
				case 3:
					mainmenu->StartGame();
					Network::GetInstance()->SendServerPacket(packet, true);
					return true;
				default:
					return false;
				}
				
            break;
        }
    }

    return false;
}
