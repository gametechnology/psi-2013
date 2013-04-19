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
	Clientlist					= guiEnv->addStaticText(L"",rect<s32>(position2di(300,105),dimension2di(200,200)),false,true,mainMenuWindow);
	Clientlist->setVisible(false);
	start_button				= guiEnv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),mainMenuWindow,3, L"Start Game");
	start_button->setVisible(false);
	Network::GetInstance()->AddListener(ClIENT_IN_LOBBY, this);

	

	
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
	if(Network::GetInstance()->connectedclients.size() >= playerlist.size() && Network::GetInstance()->IsConnected() && Network::GetInstance()->IsServer())
	{
		Player* newplayer = new Player(NULL);
		
		newplayer->Name = L"Player";
		if((playerlist.size()) % 2 != 0)
			newplayer->Team = 2;
		else
			newplayer->Team = 1;
		playerlist.push_back(newplayer);
		
	}

	NetworkPacket packet(ClIENT_IN_LOBBY);
	packet << playerlist.size();
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

		
		packet << play;
		
	}
	Network::GetInstance()->SendPacket(packet, true);
	const std::wstring& tmpp = ssp.str();
	Clientlist->setText(tmpp.c_str());


}
void MainMenuScene::StartGame()
{
	MapGenerator mapGen;
	mapGen.init(20, 2, 5);
	GalaxyMap* galaxyMap = mapGen.createNewMap(300, 300, 15);
	galaxyMap->position.set(vector3df(100, 670, 0));
	SectorManager sectorManager(galaxyMap);
	sectorManager.init();
}
void MainMenuScene::HandleNetworkMessage(NetworkPacket packet)
{
	
	int lenght;
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
		default:
			break;
	}
}


