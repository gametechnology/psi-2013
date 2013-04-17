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
        switch(event.GUIEvent.EventType)
        { 
				case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case MainMenuScene::JoinServerWindow:
					inputwchar = (wchar_t*)mainmenu->Ipadresinput->getText();
					ipadress = (char*)malloc(wcslen(inputwchar)+ 1);
					wcstombs(ipadress, inputwchar, wcslen(inputwchar));
					ipadress[wcslen(inputwchar)] = 0;
					if(*ipadress == ' ' || *ipadress == NULL){
						mainmenu->messagebox =  Game::guiEnv->addMessageBox(L"Messsage",L"Fill in an Ipadress",true,1,mainmenu->mainMenuWindow);
						mainmenu->messagebox->setDraggable(false);
					}else{
						Network::GetInstance()->InitializeClient(ipadress);
						mainmenu->messagebox =  Game::guiEnv->addMessageBox(L"Messsage",L"Connecting...",true,1,mainmenu->mainMenuWindow);
						mainmenu->messagebox->getCloseButton()->remove();
						mainmenu->messagebox->setDraggable(false);
						
					}
						
					
					return true;
				case MainMenuScene::CreateServerWindow:
					Network::GetInstance()->InitializeServer();
					mainmenu->createServerWindow_Button->setVisible(false);
					mainmenu->joinServerWindow_Button->setVisible(false);
					mainmenu->Ipadresinput->setVisible(false);
					mainmenu->start_button->setVisible(true);
					return true;
				default:
					return false;
				}
            break;
        }
    }

    return false;
}
