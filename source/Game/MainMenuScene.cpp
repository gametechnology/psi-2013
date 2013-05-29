#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(Core* core, Interface* f_interface) : Scene("MainmenuScene") 
{
	_core = core;
	_interface = f_interface;
	nextSceneRequested = nextSceneAllowed = false;
}

MainMenuScene::~MainMenuScene() 
{
	_interface->resetInterface();
	_core->resetReceiver();
	Network::GetInstance()->resetListeners();
}

void MainMenuScene::init() {
	playerlist = std::list<Player*>();

	_interface->createButton(50, 135, 200, 25, CREATE_GAME_BUTTON, 0, L"Create a game");
	_interface->createButton(50, 165, 200, 25, JOIN_GAME_BUTTON, 0, L"Join a game");

	_interface->addStaticText(L"Port:", 50, 65, 100, 25, false, true, false, 0);
	_interface->addStaticText(L"Host ip:", 175, 65, 100, 25, false, true, false, 0);
	_interface->addStaticText(L"Name:", 300, 65, 100, 25, false, true, false, 0);

	_interface->addEditBox(50, 80, 100, 25, PORT_INPUT_BOX, 0, L"", false);
	_interface->addEditBox(175, 80, 100, 25, IP_INPUT_BOX, 0, L"", true);
	_interface->addEditBox(300, 80, 100, 25, NAME_INPUT_BOX, 0, L"", true);

	Network::GetInstance()->AddListener(ClIENT_IN_LOBBY, this);
	Network::GetInstance()->AddListener(CLIENT_JOIN_DENIED, this);

	// Store the appropriate data in a context structure.
	context.core = _core;
	context.u_interface = _interface;
	context.counter = 0;

	// Then create the event receiver, giving it that context structure.
	eventReceiver = new MainMenuEventReceiver(context);

	// And tell the device to use our custom event receiver.
	_core->addCustomReceiver(eventReceiver);
}

void MainMenuScene::update()
{
	if(nextSceneRequested && nextSceneAllowed)
	{
		_core->setActiveScene(new LobbyScene(_core, _interface, playerlist));
	}
}

void MainMenuScene::requestNextScene()
{
	if(Network::GetInstance()->IsServer()) 
	{
		playerlist.push_back(new Player(
		(wchar_t*)context.u_interface->getElementWithId(NAME_INPUT_BOX)->getText(), 
		Network::GetInstance()->GetLocalAddress(), 
		1));
		nextSceneRequested = nextSceneAllowed = true;
	}
	else
		nextSceneRequested = true;
}

void MainMenuScene::requestPreviousScene()
{
	// No way back.
}

void MainMenuScene::notify(void* data)
{
}

void MainMenuScene::handleNetworkMessage(NetworkPacket packet)
{
	wchar_t *  name ;
	int lenght;
	int team;
	unsigned int ipclientaffect;

	Player* newplayer;

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
		nextSceneAllowed = true;
		break;
	case CLIENT_JOIN_DENIED:
		name = new wchar_t[500];
		packet >> name;
		packet >> ipclientaffect;
		requestPreviousScene();
		Network::GetInstance()->DeInitialize();
		_interface->addMessageBox(L"Message", name, true, 1, 0);
		break;
	default:
		break;
	}
}


