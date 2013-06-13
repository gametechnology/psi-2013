#include "MainMenuScene.h"
#include "GameScene.h"
#include "EnemySceneTest.h"
#include "PlayerManager.h"

MainMenuScene::MainMenuScene() : Scene() {
}
MainMenuScene::~MainMenuScene() {

}


void MainMenuScene::init() {
	//Get the device
	issearching = false;
	guiEnv = game->guiEnv;

	//Get the texture
	texture = game->driver->getTexture("../assets/galaxy.jpg");

	playerlist = std::list<Player*>();

	this->addGuiElements();

	Network::GetInstance()->AddListener(ClIENT_IN_LOBBY, this);
	Network::GetInstance()->AddListener(START_GAME, this);
	Network::GetInstance()->AddListener(CLIENT_JOIN, this);
	Network::GetInstance()->AddListener(CLIENT_QUIT, this);
	Network::GetInstance()->AddListener(HOST_DISCONNECT, this);
	Network::GetInstance()->AddListener(CLIENT_JOIN_DENIED, this);

	// Store the appropriate data in a context structure.
	SAppContext context;
	context.game = game;
	context.counter = 0;

	// Then create the event receiver, giving it that context structure.
	eventReceiver = new MainMenuEventReceiver(context);

	// And tell the device to use our custom event receiver.
	game->input->setCustomEventReceiver(eventReceiver);
}

void MainMenuScene::draw() {
	game->driver->draw2DImage(texture, vector2di(0,0), rect<s32>(0,0,1280,720));  
}

void MainMenuScene::addGuiElements()
{

	///////////////////////////////////////////
	// MainMenu
	//////////////////////////////////////////
	//Creat the main menu window
	IVideoDriver* driver = game->driver;

	guiEnv->addImage(game->driver->getTexture("../assets/Enemyspaceship.png"),
            position2d<int>(175,300));
	guiEnv->addImage(game->driver->getTexture("../assets/SpaceShip.png"),
            position2d<int>(400,300));
	
	mainMenuWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Main menu",0,100);
	mainMenuWindow->getCloseButton()->remove();
	
	//Add text and button
	
	createServerWindow_Button = guiEnv->addButton(rect<s32>(position2di(50,135),dimension2di(200,25)),mainMenuWindow,2, L"Create a game");
	joinServerWindow_Button	= guiEnv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),mainMenuWindow,1,L"Join a game manualy");
	findserver_Button	= guiEnv->addButton(rect<s32>(position2di(50,195),dimension2di(200,25)),mainMenuWindow,6,L"Find hosts");	
		
	servernames	= guiEnv->addStaticText(L"Server name:",rect<s32>(position2di(50,225),dimension2di(100,25)),false,true,mainMenuWindow);
	serverip = guiEnv->addStaticText(L"Server Ipadress:",rect<s32>(position2di(175,225),dimension2di(100,25)),false,true,mainMenuWindow);
	serveractions	= guiEnv->addStaticText(L"Actions:",rect<s32>(position2di(300,225),dimension2di(100,25)),false,true,mainMenuWindow);



	servernameLabel = guiEnv->addStaticText(L"Server name:",rect<s32>(position2di(50,65),dimension2di(100,25)),false,true,mainMenuWindow);
	ipLabel	= guiEnv->addStaticText(L"Host ip:",rect<s32>(position2di(300,150),dimension2di(100,25)),false,true,mainMenuWindow);
	Namelabel = guiEnv->addStaticText(L"Player Name:",rect<s32>(position2di(175,65),dimension2di(100,25)),false,true,mainMenuWindow);

	servernameInput = guiEnv->addEditBox(L"",rect<s32>(position2di(50, 80),dimension2di(100,25)),true,mainMenuWindow);
	Ipadresinput = guiEnv->addEditBox(L"",rect<s32>(position2di(300, 165),dimension2di(100,25)),true,mainMenuWindow);
	Nameinput = guiEnv->addEditBox(L"",rect<s32>(position2di(175, 80),dimension2di(100,25)),true,mainMenuWindow);

	Clientlist = guiEnv->addStaticText(L"",rect<s32>(position2di(300,105),dimension2di(200,200)),false,true,mainMenuWindow);
	Clientlist->setVisible(false);

	start_button = guiEnv->addButton(rect<s32>(position2di(350,330),dimension2di(200,25)),mainMenuWindow,3, L"Start Game");
	start_button->setVisible(false);

	startStatic_button = guiEnv->addButton(rect<s32>(position2di(350,300),dimension2di(200,25)),mainMenuWindow,4, L"Start Test Game");
	startStatic_button->setVisible(false);

	quit_button	= guiEnv->addButton(rect<s32>(position2di(50,330),dimension2di(200,25)),mainMenuWindow,5, L"Quit game");
	quit_button->setVisible(false);

	waitinglabel = guiEnv->addStaticText(L"Waiting for host to start the game",rect<s32>(position2di(300,165),dimension2di(200,25)),false,true,mainMenuWindow);
	waitinglabel->setVisible(false);

	Scene::addGuiElements();
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
	if(Network::GetInstance()->IsServer())
	{
		sf::UdpSocket Socket;
		sf::Packet sendpacket;
		wchar_t* inputwchar = (wchar_t*)servernameInput->getText();
		
		sendpacket << true;
		sendpacket << inputwchar;
		// Send data to "192.168.0.2" on port 4567
		if (Socket.send(sendpacket, "145.92.13.203", 4444) != sf::Socket::Done)
		{
			// Error...
		}
	}
	if(issearching)
	{
		sf::UdpSocket Socket;
		sf::Packet sendpacket;
		sendpacket << false;
		// Send data to "192.168.0.2" on port 4567
		if (Socket.send(sendpacket, "145.92.13.203", 4444) != sf::Socket::Done)
		{
			// Error...
		}
	}
	

	//Ask playermanager to get all player info from the server, when L is pressed
	if (game->input->isKeyboardButtonDown(irr::KEY_KEY_L))
		PlayerManager::GetInstance()->SendPlayerInfoRequest();
}

void MainMenuScene::StartGame()
{
	cout << endl << "MainMenuScene::StartGame() - not yet implemented" << endl;
	/*MapGenerator mapGen;
	mainMenuWindow->remove();
	mapGen.init(20, 2, 5);
	GalaxyMap* galaxyMap = mapGen.createNewMap(300, 300, 15);
	galaxyMap->transform->position->set(vector3df(100, 670, 0));
	SectorManager sectorManager(galaxyMap);
	sectorManager.init();*/
	//TODO: Previous scene still displayed, shouldn't be the case
	this->game->guiEnv->clear();
	this->game->sceneManager->deactivateScene("MainMenuScene");
	this->game->sceneManager->addScene("GameScene",new GameScene(playerlist));
}

void MainMenuScene::StartTestGame()
{
	cout << endl << "MainMenuScene::StartGame() - not yet implemented" << endl;
	//TODO: Previous scene still displayed, shouldn't be the case
	this->game->guiEnv->clear();
	this->game->sceneManager->deactivateScene("MainMenuScene");
	this->game->sceneManager->addScene("GameScene",new GameScene(playerlist, true));
}

void MainMenuScene::HandleNetworkMessage(NetworkPacket packet)
{
	wchar_t *  name ;
	int lenght;
	int team;
	unsigned int ipclientaffect;
	unsigned int checksum;
	sf::IpAddress localip;
	Player* newplayer;
	std::list<Player*>::const_iterator iterator;

	NetworkPacket deniedpack(CLIENT_JOIN_DENIED);
	NetworkPacket packetsend(ClIENT_IN_LOBBY);

	switch(packet.GetType())
	{
	case ClIENT_IN_LOBBY:
		if(!Network::GetInstance()->IsServer()){
			playerlist.clear();
			packet >> lenght;
			for (int i = 0;i < lenght;i++){
				Player * newplayer;
				newplayer = new Player();
				packet >> newplayer;
				playerlist.push_back(newplayer);
			}
		}
		break;
	case CLIENT_JOIN_DENIED:
		name = new wchar_t[500];
		packet >> name;
		packet >> ipclientaffect;
		localip = sf::IpAddress::getLocalAddress();
		checksum = localip.m_address;

		if (ipclientaffect == checksum){
			BackToMainMenu();
			Network::GetInstance()->DeInitialize();
			messagebox =  game->guiEnv->addMessageBox(L"Message",name,true,1,mainMenuWindow);
		}
		delete name;
		break;
	case START_GAME:
		StartGame();
		break;
	case CLIENT_JOIN:
		name = new wchar_t[500];
		packet >> name;
		packet >> checksum;

		if(checksum != Network::GetInstance()->GetPacketTypeChecksum())
		{
			deniedpack << L"Your version does not match with the version of the host";
			deniedpack << packet.GetSender().address.host;
			Network::GetInstance()->SendServerPacket(deniedpack, true);
			return;
		}
		for (iterator = playerlist.begin(); iterator != playerlist.end(); ++iterator){
			if((*iterator)->Ipadres == packet.GetSender().address.host){
				deniedpack << L"Your pc is already connected to the host";
				deniedpack << packet.GetSender().address.host;
				Network::GetInstance()->SendServerPacket(deniedpack, true);

				return;
			}

		}
		if((playerlist.size()) % 2 != 0)
			team = 2;
		else
			team = 1;
		newplayer = new Player( name,  packet.GetSender().address.host, team);
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
			if((*iterator)->Ipadres == packet.GetSender().address.host)
				newplayer = (*iterator);

		}
		if(newplayer == NULL)
			return;
		playerlist.remove(newplayer);
		lenght = playerlist.size();
		packetsend << lenght;
		lenght = 0;
		for (iterator = playerlist.begin(); iterator != playerlist.end(); ++iterator){
			if(lenght != 0 && (lenght) % 2 != 0)
				(*iterator)->Team = 2;
			else
				(*iterator)->Team = 1;
			packetsend << (*iterator);
			lenght++;
		}
		Network::GetInstance()->SendServerPacket(packetsend, true);
		break;
		break;
	case HOST_DISCONNECT:
		name = new wchar_t[500];
		packet >> name;
		playerlist.clear();
		messagebox =  game->guiEnv->addMessageBox(L"Message",name,true,1,mainMenuWindow);
		Network::GetInstance()->DeInitialize();
		BackToMainMenu();
		delete name;
		break;
	default:
		break;
	}
}

void MainMenuScene::BackToMainMenu()
{
	createServerWindow_Button->setVisible(true);
	joinServerWindow_Button->setVisible(true);
	ipLabel->setVisible(true);
	Ipadresinput->setVisible(true);
	Namelabel->setVisible(true);
	Nameinput->setVisible(true);
	Clientlist->setVisible(false);
	start_button->setVisible(false);
	servernameInput->setVisible(true);
	servernameLabel->setVisible(true);
	findserver_Button->setVisible(true);
	startStatic_button->setVisible(false);
	quit_button->setVisible(false);
	waitinglabel->setVisible(false);
	servernames->setVisible(true);
	serveractions->setVisible(true);
	serverip->setVisible(true);
	
}

void MainMenuScene::serverlistreciever(void * menu){
	sf::UdpSocket Socket;
	MainMenuScene * mainmenu = (MainMenuScene*)menu;
		// Bind it (listen) to the port 4567
		if (!Socket.bind(4567))
		{
			// Error...
		}
		sf::Packet recievepacket;
		sf::IpAddress Sender;
		unsigned short Port;
		std::cout << "waiting for packet...\n";
		if (Socket.receive(recievepacket, Sender, Port) != sf::Socket::Done)
		{
			// Error...
		}
		else
		{
		}
		mainmenu->issearching = false;
		std::list<irr::gui::IGUIElement*>::iterator iterator;
								for (iterator = mainmenu->lisitems.begin(); iterator != mainmenu->lisitems.end(); ++iterator) {		
									(*iterator)->remove();

								}
								mainmenu->lisitems.clear();
		int length;
		 recievepacket >> length;
		int height = 255;
		
		for (int i =0;i < length; i++)
		{ 
			std::wstring s;
			
			host newhost;
			wchar_t*name = new wchar_t[500];
			
			newhost.name = new wchar_t[500];
			newhost.id = i + 7;
			
			recievepacket >> newhost.ipadress;
			recievepacket >> name;

			s.assign(newhost.ipadress.begin(), newhost.ipadress.end());
			wcsncpy(newhost.name, name, wcslen(name));
			newhost.name[wcslen(name)] = 0;
			mainmenu->hostlist.push_back(newhost);
			delete name;
			mainmenu->lisitems.push_back(mainmenu->guiEnv->addStaticText(newhost.name,rect<s32>(position2di(50,height),dimension2di(100,25)),false,true,mainmenu->mainMenuWindow));
			mainmenu->lisitems.push_back(mainmenu->guiEnv->addStaticText(s.c_str(),rect<s32>(position2di(175,height),dimension2di(100,25)),false,true,mainmenu->mainMenuWindow));
			mainmenu->lisitems.push_back(mainmenu->guiEnv->addButton(rect<s32>(position2di(300,height),dimension2di(200,25)),mainmenu->mainMenuWindow,7 + i, L"Join game"));


			height += 30;
		}
		
}


