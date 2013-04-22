#include "Engine/Game.h"
#include "MainMenuScene.h"



MainMenuScene::MainMenuScene() 
{
	//Get the device
	guiEnv = Game::guiEnv;
	playerlist = std::list<Player*>();

	///////////////////////////////////////////
	// MainMenu
	//////////////////////////////////////////
	//Creat the main menu window
	mainMenuWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Main menu",0,100);
	mainMenuWindow->getCloseButton()->remove();

	//Add text and button
	createServerWindow_Button	= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),mainMenuWindow,2, L"Create a game");
	joinServerWindow_Button		= guiEnv->addButton(rect<s32>(position2di(50,135),dimension2di(200,25)),mainMenuWindow,1,L"Join a game");
	Ipadresinput				= guiEnv->addEditBox(L"",rect<s32>(position2di(300,135),dimension2di(200,25)),true,mainMenuWindow);
	Namelabel					= guiEnv->addStaticText(L"Name:",rect<s32>(position2di(250,165),dimension2di(200,25)),false,true,mainMenuWindow);
	Nameinput					= guiEnv->addEditBox(L"",rect<s32>(position2di(300,165),dimension2di(200,25)),true,mainMenuWindow);
	Clientlist					= guiEnv->addStaticText(L"",rect<s32>(position2di(300,105),dimension2di(200,200)),false,true,mainMenuWindow);
	Clientlist->setVisible(false);
	start_button				= guiEnv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),mainMenuWindow,3, L"Start Game");
	start_button->setVisible(false);
	Network::GetInstance()->AddListener(ClIENT_IN_LOBBY, this);
	Network::GetInstance()->AddListener(START_GAME, this);
	Network::GetInstance()->AddListener(CLIENT_JOIN, this);
	Network::GetInstance()->AddListener(CLIENT_QUIT, this);

	

	
	 // Store the appropriate data in a context structure.
    SAppContext context;
	context.device = Game::device;
    context.counter = 0;

	// Then create the event receiver, giving it that context structure.
	eventReceiver = new MainMenuEventReceiver(context);

    // And tell the device to use our custom event receiver.
	Game::input->setCustomEventReceiver(eventReceiver);
}

MainMenuScene::~MainMenuScene()
{
}
void MainMenuScene::update(){
	
	std::wstringstream ssp;
	ssp << L"Team 1              Team2\n";
	std::list<Player*>::const_iterator iterator;
	for (iterator = playerlist.begin(); iterator != playerlist.end(); ++iterator){
		Player *play = (*iterator);

		ssp << play->Name;
		 if(play->Team == 1)
			 ssp << L"              ";
		 else
			ssp << L"\n";

		
		
		
	}

	const std::wstring& tmpp = ssp.str();
	Clientlist->setText(tmpp.c_str());


}
void MainMenuScene::StartGame()
{
	mainMenuWindow->remove();
	MapGenerator mapGen;
	mapGen.init(20, 2, 5);
	GalaxyMap* galaxyMap = mapGen.createNewMap(300, 300, 15);
	galaxyMap->position.set(vector3df(100, 670, 0));
	SectorManager sectorManager(galaxyMap);
	sectorManager.init();
}
void MainMenuScene::HandleNetworkMessage(NetworkPacket packet)
{
	wchar_t *  name ;
	int lenght;
	int team;
	unsigned int checksum;
	Player* newplayer;
	std::list<Player*>::const_iterator iterator;
	NetworkPacket packetsend(ClIENT_IN_LOBBY);
	switch(packet.GetType())
	{
		case ClIENT_IN_LOBBY:
			if(!Network::GetInstance()->IsServer()){
				playerlist.clear();
				packet >> lenght;
				for (int i = 0;i < lenght;i++){
					Player * newplayer;
					newplayer = new Player(NULL);
					packet >> newplayer;
					playerlist.push_back(newplayer);
				}
			}
		break;
		case START_GAME:
			StartGame();
			break;
		case CLIENT_JOIN:
			name = new wchar_t[500];
			packet >> name;
			packet >> checksum;
			
			if(checksum != Network::GetInstance()->GetPacketTypeChecksum())
				return;

			for (iterator = playerlist.begin(); iterator != playerlist.end(); ++iterator){
				if((*iterator)->Ipadres == packet.ipadress)
					return;
					
			}
			if((playerlist.size()) % 2 != 0)
				team = 2;
			else
				team = 1;
			newplayer = new Player(NULL, name,  packet.ipadress, team);
			playerlist.push_back(newplayer);
			
			lenght = playerlist.size();
			packetsend << lenght;
			
			for (iterator = playerlist.begin(); iterator != playerlist.end(); ++iterator){
				 
				packetsend << (*iterator);
			}
			Network::GetInstance()->SendServerPacket(packetsend, true);
			delete name;
			break;
		case CLIENT_QUIT:
			for (iterator = playerlist.begin(); iterator != playerlist.end(); ++iterator){
				if((*iterator)->Ipadres == packet.ipadress)
					newplayer = (*iterator);
					
			}
			playerlist.remove(newplayer);
			lenght = playerlist.size();
			packetsend << lenght;
			for (iterator = playerlist.begin(); iterator != playerlist.end(); ++iterator){
				 
				packetsend << (*iterator);
			}
			Network::GetInstance()->SendServerPacket(packetsend, true);
			break;
		break;
		default:
			break;
	}
}


