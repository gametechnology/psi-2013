#include "MainMenuEventReceiver.h"
#include "MainMenuScene.h"
#include "Engine\Network.h"
#include "NetworkInterface.h"
#include "PlayerManager.h"

MainMenuEventReceiver::MainMenuEventReceiver(SAppContext & context) : Context(context) {
	this->contextGame = context.game;
}

bool MainMenuEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		IGUIEnvironment* env = this->contextGame->guiEnv;
		MainMenuScene* mainmenu = ((MainMenuScene*)this->contextGame->sceneManager->getLastScene());
		char* ipadress;
		wchar_t* inputwchar;

		char* playername;
		wchar_t* namewchar;
		host currhost;
	wchar_t* servername;
		Player* newplayer;
		NetworkPacket packet(START_GAME);
		NetworkPacket namepacket(CLIENT_JOIN);
		NetworkPacket quitpacket(CLIENT_QUIT);
		NetworkPacket hostquitpacket(HOST_DISCONNECT);

		switch(event.GUIEvent.EventType)
		{ 
		case EGET_BUTTON_CLICKED:
			switch(id)
			{
			case 1: // Join
				inputwchar = (wchar_t*)mainmenu->Ipadresinput->getText();
				ipadress = (char*)malloc(wcslen(inputwchar)+ 1);
				wcstombs(ipadress, inputwchar, wcslen(inputwchar));
				ipadress[wcslen(inputwchar)] = 0;

			

				namewchar = (wchar_t*)mainmenu->Nameinput->getText();
				playername = (char*)malloc(wcslen(namewchar)+ 1);
				wcstombs(playername, namewchar, wcslen(namewchar));
				playername[wcslen(namewchar)] = 0;

				if((*ipadress == ' ' || *ipadress == NULL) || (*playername == ' ' || *playername == NULL)){
					if(*ipadress == ' ' || *ipadress == NULL){
						mainmenu->messagebox =  env->addMessageBox(L"Messsage",L"Fill in an Ipadress",true,1,mainmenu->mainMenuWindow);
						mainmenu->messagebox->setDraggable(false);
					}else{
						mainmenu->messagebox = this->contextGame->guiEnv->addMessageBox(L"Message",L"Fill in an Name",true,1,mainmenu->mainMenuWindow);
						mainmenu->messagebox->setDraggable(false);
					}
				}else{
					Network::GetInstance()->InitializeClient(ipadress);
					if(!Network::GetInstance()->IsConnected()){
						mainmenu->messagebox =  env->addMessageBox(L"Messsage",L"Not able to connect to server",true,1,mainmenu->mainMenuWindow);
						mainmenu->messagebox->setDraggable(false);
					}else{
						PlayerManager::GetInstance()->Init();
						PlayerManager::GetInstance()->SetGame(this->contextGame);
						//TODO: package met naam en checksum: Network->getinstance->GetPacketTypeChecksum
						namepacket << namewchar << Network::GetInstance()->GetPacketTypeChecksum();
						Network::GetInstance()->SendPacket(namepacket, true);
						mainmenu->createServerWindow_Button->setVisible(false);
						mainmenu->joinServerWindow_Button->setVisible(false);
						mainmenu->Clientlist->setVisible(true);
						mainmenu->Ipadresinput->setVisible(false);
						mainmenu->Namelabel->setVisible(false);
						mainmenu->findserver_Button->setVisible(false);
						mainmenu->servernameInput->setVisible(false);
						mainmenu->servernameLabel->setVisible(false);
											mainmenu->servernames->setVisible(false);
					mainmenu->serveractions->setVisible(false);
					mainmenu->serverip->setVisible(false);
						// TODO check merge Both??
						mainmenu->waitinglabel = env->addStaticText(L"Waiting for host to start the game",rect<s32>(position2di(300,165),dimension2di(200,25)),false,true,mainmenu->mainMenuWindow);
						mainmenu->Nameinput->setVisible(false);
						mainmenu->quit_button->setVisible(true);
						mainmenu->waitinglabel->setVisible(true);
							std::list<irr::gui::IGUIElement*>::iterator iterator;
								for (iterator = mainmenu->lisitems.begin(); iterator != mainmenu->lisitems.end(); ++iterator) {		
									(*iterator)->remove();

								}
								mainmenu->lisitems.clear();
						//TODO Proper team implementation
						PlayerManager::GetInstance() -> RequestJoinServer( playername );
					}
				}


				return true;
			case 2: // Create
				namewchar = (wchar_t*)mainmenu->Nameinput->getText();
				playername = (char*)malloc(wcslen(namewchar)+ 1);
				 servername = (wchar_t*)mainmenu->servernameInput->getText();
				wcstombs(playername, namewchar, wcslen(namewchar));
				playername[wcslen(namewchar)] = 0;

				if(*playername == ' ' || wcslen(servername) == 0  || *playername == NULL){
					mainmenu->messagebox = this->contextGame->guiEnv->addMessageBox(L"Message",L"Fill in a name and server name",true,1,mainmenu->mainMenuWindow);
					mainmenu->messagebox->setDraggable(false);
					return false;
				}else{
					Network::GetInstance()->InitializeServer();
					PlayerManager::GetInstance()->Init();
					mainmenu->createServerWindow_Button->setVisible(false);
					mainmenu->joinServerWindow_Button->setVisible(false);
					mainmenu->ipLabel->setVisible(false);
					mainmenu->Ipadresinput->setVisible(false);
					mainmenu->Namelabel->setVisible(false);
					mainmenu->Nameinput->setVisible(false);
					mainmenu->servernameInput->setVisible(false);
					mainmenu->servernameLabel->setVisible(false);
					mainmenu->findserver_Button->setVisible(false);
					mainmenu->start_button->setVisible(true);
					mainmenu->startStatic_button->setVisible(true);
					mainmenu->quit_button->setVisible(true);
					mainmenu->servernames->setVisible(false);
					mainmenu->serveractions->setVisible(false);
					mainmenu->serverip->setVisible(false);
					mainmenu->Clientlist->setVisible(true);
					newplayer = new Player();
					newplayer->Name = namewchar;
					newplayer->Team = 1;
					newplayer->Ipadres = Network::GetInstance()->GetLocalAddress();
					mainmenu->playerlist.push_back(newplayer);
						std::list<irr::gui::IGUIElement*>::iterator iterator;
								for (iterator = mainmenu->lisitems.begin(); iterator != mainmenu->lisitems.end(); ++iterator) {		
									(*iterator)->remove();

								}
								mainmenu->lisitems.clear();
					//the host is always on team 1
					PlayerManager::GetInstance() -> RequestJoinServer( playername );

					return true;
				}
			case 3: // Start
				mainmenu->StartGame();
				Network::GetInstance()->SendServerPacket(packet, true);
				return true;
			case 4: // Start Test Map
				mainmenu->StartTestGame();
				Network::GetInstance()->SendServerPacket(packet, true);
				return true;
			case 5: // Quit
				if(!Network::GetInstance()->IsServer())
				{
					Network::GetInstance()->SendPacket(quitpacket, true);
				}
				else
				{
					hostquitpacket << L"The host got disconnected";
					Network::GetInstance()->SendServerPacket(hostquitpacket, true);

				}
				mainmenu->playerlist.clear();
				Network::GetInstance()->DeInitialize();
				mainmenu->BackToMainMenu();
				return true;
			case 6:
				mainmenu->issearching = true;
				_beginthread(mainmenu->serverlistreciever,0,mainmenu);
				return true;

			default:
				if(id >= 7)
					{
						
						std::list<host>::iterator iterator;
						for (iterator = mainmenu->hostlist.begin(); iterator != mainmenu->hostlist.end(); ++iterator) {		
							if((*iterator).id == id){
								currhost = (*iterator);
						
								 break;
							}
						}
				
						namewchar = (wchar_t*)mainmenu->Nameinput->getText();
						playername = (char*)malloc(wcslen(namewchar)+ 1);
						wcstombs(playername, namewchar, wcslen(namewchar));
						playername[wcslen(namewchar)] = 0;
			


						if( (*playername == ' ' || *playername == NULL)){
					
					
								mainmenu->messagebox = this->contextGame->guiEnv->addMessageBox(L"Message",L"Fill in an Name",true,1,mainmenu->mainMenuWindow);
								mainmenu->messagebox->setDraggable(false);
					
						}else{
							Network::GetInstance()->InitializeClient(currhost.ipadress.c_str());
							if(!Network::GetInstance()->IsConnected()){
								mainmenu->messagebox =  env->addMessageBox(L"Messsage",L"Not able to connect to server",true,1,mainmenu->mainMenuWindow);
								mainmenu->messagebox->setDraggable(false);
							}else{
								PlayerManager::GetInstance()->Init();
								//TODO: package met naam en checksum: Network->getinstance->GetPacketTypeChecksum
								namepacket << namewchar << Network::GetInstance()->GetPacketTypeChecksum();
								Network::GetInstance()->SendPacket(namepacket, true);
								mainmenu->createServerWindow_Button->setVisible(false);
								mainmenu->joinServerWindow_Button->setVisible(false);
								mainmenu->Clientlist->setVisible(true);
								mainmenu->Ipadresinput->setVisible(false);
								mainmenu->Namelabel->setVisible(false);
								mainmenu->findserver_Button->setVisible(false);
								mainmenu->servernameInput->setVisible(false);
								mainmenu->servernameLabel->setVisible(false);
													mainmenu->servernames->setVisible(false);
							mainmenu->serveractions->setVisible(false);
							mainmenu->serverip->setVisible(false);
								// TODO check merge Both??
								mainmenu->waitinglabel = env->addStaticText(L"Waiting for host to start the game",rect<s32>(position2di(300,165),dimension2di(200,25)),false,true,mainmenu->mainMenuWindow);
								mainmenu->Nameinput->setVisible(false);
								mainmenu->quit_button->setVisible(true);
								mainmenu->waitinglabel->setVisible(true);

								std::list<irr::gui::IGUIElement*>::iterator iterator;
								for (iterator = mainmenu->lisitems.begin(); iterator != mainmenu->lisitems.end(); ++iterator) {		
									(*iterator)->remove();

								}
								mainmenu->lisitems.clear();
								//TODO Proper team implementation
								PlayerManager::GetInstance() -> RequestJoinServer( playername);
							}
						}
					}
				return false;
			}
			

			break;
		}

	}

	return false;
}
