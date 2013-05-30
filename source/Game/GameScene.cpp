#include "GameScene.h"

using namespace irr;
using namespace irr::core;

GameScene::GameScene(Core* core, Interface* ui, std::list<Player*> playerList, bool isTestMap) : Scene("GameScene")
{
	this->testMap = isTestMap;
	
	_playerList = playerList;
	_core = core;
	_interface = ui;

	Network::GetInstance()->AddListener(CLIENT_SWITCH_STATION, this);
	Network::GetInstance()->AddListener(CLIENT_FIRE_LASER, this);
	Network::GetInstance()->AddListener(SERVER_LASER, this);
	Network::GetInstance()->AddListener(SERVER_WINLOSE, this);
}

void GameScene::init() {
	SendAndReceivePackets::core = _core;

	_sendLasersTimer = 0;
	_laserPool = new ObjectPool<Laser>(*this, _core, 100);
	
	EnemyFighter::laserPool = _laserPool;
	Ship::laserPool = _laserPool;

	_ship = new Ship(_core, _interface, vector3df(0,0,0), vector3df(0,0,0));
	addComponent(_ship);

	addComponent(new CameraComponent(_core->getSmgr(), CameraComponent::THIRD_PERSON));

	_shipEnemy = new Ship(_core, _interface, vector3df(0,0,-100), vector3df(180,0,0));
	addComponent(_shipEnemy);

	BasicMoverComponent* movComp = new BasicMoverComponent(_ship);
	_shipEnemy->addComponent(movComp);

	//Creates Map & SectorManager
	GalaxyMap* galaxyMap = new GalaxyMap(_core, 300, 300, 15);

	/*if (!testMap)
		galaxyMap->createMap(20, 2, 5);
	else*/
		galaxyMap->createStaticMap();

	galaxyMap->setPosition(new vector3df(100, 670, 0));

	printf("-----------Added SectorManager----------\n\n");
	addComponent(new SectorManager(this, _core, galaxyMap, _ship));

	_shipmap = new Shipmap(_core, this);
	addComponent(_shipmap);

	Scene::init();
}

void GameScene::update() {
	if(Network::GetInstance()->IsServer())
	{
		this->_sendLasersTimer++;
		if(this->_sendLasersTimer > 50)
		{
			SendAndReceivePackets::sendLazerPacket(this->_laserPool->getAllObjects());
			this->_sendLasersTimer = 0;
		}
		
		/*TODO:
		Edit code below to make it send a winlose packet when one of the ship reaches health of 0
		and give the right team id as the parameter*/
		
		if(_core->getInput()->isKeyboardButtonDown(KEY_KEY_Z) || _ship->getShipHealth() <= 0 || _shipEnemy->getShipHealth() <= 0)
		{
			SendAndReceivePackets::sendWinLosePacket(1);
			SendAndReceivePackets::handleWinLose(1, 2, this);
		}
	}

	Scene::update();
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::requestNextScene()
{
}

void GameScene::requestPreviousScene()
{
}

void GameScene::notify(void* data)
{
}

void GameScene::handleNetworkMessage(NetworkPacket packet)
{
	std::cout<< packet.GetType() << std::endl;

	switch(packet.GetType())
	{
	case SERVER_LASER:
		this->_laserPool->setAllObjects(SendAndReceivePackets::receiveLaserPacket(packet, this->_laserPool->getAllObjects(), this));
		break;
	case SERVER_WINLOSE:
		SendAndReceivePackets::receiveWinLosePacket(packet, 1, this);
		break;
	case CLIENT_SWITCH_STATION:
		for(std::list<Player*>::iterator i=_playerList.begin(); i!=_playerList.end(); ++i)
		{			
			if((*i)->Ipadres == packet.GetSender().address.host)
			{
				unsigned int receivedStationType;
				packet >> receivedStationType;
				if(_ship->GetStation((StationType)receivedStationType)->setPlayerOccupation((*i)) == false)
					printf("Code is not handling stations correctly. This error originates in [GameScene.cpp] in function [HandleNetworkMessage].\n");
			}
		}
		break;
	case CLIENT_LEAVE_STATION:
		for(std::list<Player*>::iterator i=_playerList.begin(); i!=_playerList.end(); ++i)
		{			
			if((*i)->Ipadres == packet.GetSender().address.host)
			{
				unsigned int receivedStationType;
				packet >> receivedStationType;
				_ship->GetStation((StationType)receivedStationType)->resetPlayerOccupation();
			}
		}
		break;
	case CLIENT_FIRE_LASER:
		_laserPool->setAllObjects(SendAndReceivePackets::receiveLaserPacketFromClient(packet, _laserPool->getAllObjects(), this, _core->getSmgr()));
	}
}

void GameScene::switchStation(StationType type)
{
	_shipmap->setEnabled(false);

	_ship->SwitchToStation(type, *_playerList.begin());
}

GameScene::~GameScene() 
{
	delete _laserPool;
	Scene::~Scene();
}
