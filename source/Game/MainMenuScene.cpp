#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(Core* core, Interface* f_interface) : Scene("MainmenuScene") 
{
	_core = core;
	_interface = f_interface;
}

MainMenuScene::~MainMenuScene() 
{
	_interface->resetInterface();
}

void MainMenuScene::init() {
	playerlist = std::list<Player*>();

	_interface->createButton(50, 135, 150, 110, 0, 0, L"Create a game");
	_interface->createButton(50, 165, 150, 110, 0, 0, L"Join a game");

	_interface->addStaticText(L"Port:", 50, 65, 50, 40, false, true, false, 0);
	_interface->addStaticText(L"Host ip:", 50, 65, 50, 40, false, true, false, 0);
	_interface->addStaticText(L"Port:", 50, 65, 50, 40, false, true, false, 0);

	_interface->addEditBox(50, 80, 50, 55, PORT_INPUT_BOX, 0, L"", true);
	_interface->addEditBox(175, 80, 50, 55, IP_INPUT_BOX, 0, L"", true);
	_interface->addEditBox(300, 80, 50, 55, NAME_INPUT_BOX, 0, L"", true);

	// Store the appropriate data in a context structure.
	SAppContext context;
	context.core = _core;
	context.counter = 0;

	// Then create the event receiver, giving it that context structure.
	eventReceiver = new MainMenuEventReceiver(context);

	// And tell the device to use our custom event receiver.
	_core->addCustomReceiver(eventReceiver);
}

void MainMenuScene::update()
{

}

void MainMenuScene::requestNextScene()
{
	_core->setActiveScene(new LobbyScene(_core, _interface));
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
		requestPreviousScene();
		Network::GetInstance()->DeInitialize();
		_interface->addMessageBox(L"Message", name, true, 1, 0);
		break;
	case START_GAME:
		requestNextScene();
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


