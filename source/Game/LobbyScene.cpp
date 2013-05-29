#include "LobbyScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"

LobbyScene::LobbyScene(Core* core, Interface* ui, std::list<Player*> playerlist) : Scene("LobbyScene")
{
	_core = core;
	_interface = ui;
	this->playerlist = playerlist;

	nextSceneRequested = nextSceneAllowed = false;
}

LobbyScene::~LobbyScene()
{
	_interface->resetInterface();
	_core->resetReceiver();
	Network::GetInstance()->resetListeners();
}

void LobbyScene::init()
{
	_interface->addStaticText(L"", 300, 105, 200, 200, CLIENT_LIST, false, true, false, 0);
	_interface->createButton(50, 330, 200, 25, QUIT_GAME_BUTTON, 0, L"Quit game");

	if(Network::GetInstance()->IsServer())
		_interface->createButton(350, 330, 200, 25, START_GAME_BUTTON, 0, L"Start Game");
	else
		_interface->addStaticText(L"Waiting for host to start the game", 300, 165, 100, 140, -1, false, true, false);

	Network::GetInstance()->AddListener(START_GAME, this);
	Network::GetInstance()->AddListener(CLIENT_JOIN, this);
	Network::GetInstance()->AddListener(CLIENT_QUIT, this);
	Network::GetInstance()->AddListener(HOST_DISCONNECT, this);

	// Store the appropriate data in a context structure.
	context.core = _core;
	context.u_interface = _interface;
	context.counter = 0;

	// Then create the event receiver, giving it that context structure.
	eventReceiver = new MainMenuEventReceiver(context);

	// And tell the device to use our custom event receiver.
	_core->addCustomReceiver(eventReceiver);
}

void LobbyScene::update()
{
	std::wstringstream ssp;
	ssp << L"Team 1              Team2\n";

	for (std::list<Player*>::iterator it = playerlist.begin(); it != playerlist.end(); ++it){
		ssp << (*it)->Name;
		if((*it)->Team == 1)
			ssp << L"              ";
		else
			ssp << L"\n";
	}

	const std::wstring& tmpp = ssp.str();

	_interface->getElementWithId(CLIENT_LIST)->setText(tmpp.c_str());

	if(nextSceneRequested && nextSceneAllowed)
	{
		_core->setActiveScene(new GameScene(_core, _interface, playerlist));
	}
}

void LobbyScene::draw()
{
	Scene::draw();
}

void LobbyScene::notify(void* data)
{
}

void LobbyScene::requestNextScene()
{
	nextSceneRequested = nextSceneAllowed = true;
}

void LobbyScene::requestPreviousScene()
{
	_core->setActiveScene(new MainMenuScene(_core, _interface));
}

void LobbyScene::handleNetworkMessage(NetworkPacket packet)
{
	int lenght;
	int team;
	unsigned int ipclientaffect;
	unsigned int checksum;

	Player* newplayer;
	std::list<Player*>::iterator iterator;

	wchar_t* name = new wchar_t[500];

	NetworkPacket deniedpack(CLIENT_JOIN_DENIED);
	NetworkPacket packetsend(ClIENT_IN_LOBBY);

	switch(packet.GetType())
	{
	case START_GAME:
		requestNextScene();
		break;
	case CLIENT_JOIN:

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

		newplayer = new Player(name,  packet.GetSender().address.host, team);
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
	case HOST_DISCONNECT:
		name = new wchar_t[500];
		packet >> name;
		playerlist.clear();
		_interface->addMessageBox(L"Message", name, true, 1, 0);
		Network::GetInstance()->DeInitialize();
		requestPreviousScene();
		delete name;
		break;
	default:
		break;
	}
}