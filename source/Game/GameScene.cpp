#include "GameScene.h"
#include "MapGenerator.h"
#include "SectorManager.h"
#include "Shipmap.h"
#include "SendAndReceivePackets.h"

GameScene::GameScene(std::list<Player*> playerList, bool isTestMap) : Scene()
{
	this->testMap = isTestMap;
	_playerList = playerList;
	Network::GetInstance()->AddListener(CLIENT_SWITCH_STATION, this);
	Network::GetInstance()->AddListener(PacketType::CLIENT_FIRE_LASER, this);
	Network::GetInstance()->AddListener(SERVER_LASER, this);
	Network::GetInstance()->AddListener(SERVER_WINLOSE, this);
}

void GameScene::onAdd() {
	SendAndReceivePackets::staticGame = this->game;

	this->_sendLasersTimer = 0;
	this->_laserPool = new ObjectPool<Laser>(*this, 100);
	EnemyFighter::laserPool = _laserPool;
	Ship::laserPool = _laserPool;

	_ship = new Ship(vector3df(0,0,0), vector3df(0,0,0));
	addChild(_ship);

	_camera = new Camera(); 
	_ship->addChild(_camera);
	_camera->init();

	//_shipEnemy = new Ship(vector3df(0,0,-100), vector3df(180,0,0));
	//addChild(_shipEnemy);

	//BasicMoverComponent* movComp = new BasicMoverComponent();
	//_shipEnemy->addComponent(movComp);

	//Creates Map & SectorManager
	galaxyMap = new GalaxyMap(300, 300, 15);

	if (!testMap) {
		galaxyMap->createMap(20, 2, 5);
	} else {
		galaxyMap->createStaticMap();
	}
	galaxyMap->transform->position = new vector3df(980, 420, 0);
	printf("-----------Added SectorManager----------\n\n");
	addChild(galaxyMap);
	addComponent(new SectorManager(galaxyMap,_ship));

	_shipmap = new Shipmap(this);
	addChild(_shipmap);

	_ship->addIShipListener(this);
}

void GameScene::init() {
	Scene::init();
}

void GameScene::update() {
	if (this->game->input->isKeyboardButtonDown(KEY_KEY_M)) {
		galaxyMap->visible = true;
	} else {
		galaxyMap->visible = false;
	}

	if(Network::GetInstance()->IsServer())
	{
		this->_sendLasersTimer++;
		if(this->_sendLasersTimer > 50)
		{
			SendAndReceivePackets::sendLazerPacket(this->_laserPool->getAllObjects());
			this->_sendLasersTimer = 0;
		}
		/*
		TODO:
		Edit code below to make it send a winlose packet when one of the ship reaches health of 0
		and give the right team id as the parameter
		*/
		if(this->game->input->isKeyboardButtonPressed(KEY_KEY_Z))
		{
			_ship->shipHealthComponent->setHealth(0);
		}

		if(this->_ship->getShipHealth() <= 0 /*|| this->_shipEnemy->getShipHealth() <= 0*/)
		{
			int otherTeamId;
			int myTeamId = PlayerManager :: GetInstance( ) -> GetLocalPlayerData( ) -> team_id;
			if( myTeamId == 1)
			{
				otherTeamId = 2;
			}else {
				otherTeamId=1;
			}

			if(_ship->getShipHealth()<=0)
			{				
				SendAndReceivePackets::sendWinLosePacket(myTeamId);
				SendAndReceivePackets::handleWinLose(myTeamId, myTeamId, this);
			}
			 /*if(_shipEnemy->getShipHealth()<=0)
			{
				SendAndReceivePackets::sendWinLosePacket(otherTeamId);
				SendAndReceivePackets::handleWinLose(otherTeamId, otherTeamId, this);
			}*/
			/*SendAndReceivePackets::sendWinLosePacket(1);
			SendAndReceivePackets::handleWinLose(1, 2, this);*/
		}		
	}
	if ( this -> game -> input -> isKeyboardButtonPressed( KEY_TAB ) )
	{
		PlayerManager :: GetInstance( ) -> ShowPlayerList( );
		std :: cout << "\n-------------------------------\n";
	}

	Scene::update();
}

void GameScene::HandleNetworkMessage(NetworkPacket packet)
{
	std::cout<< packet.GetType() << endl;

	switch(packet.GetType())
	{
	case SERVER_LASER:
		this->_laserPool->setAllObjects(SendAndReceivePackets::receiveLaserPacket(packet, this->_laserPool->getAllObjects(), this));
		break;
	case SERVER_WINLOSE:
		SendAndReceivePackets::receiveWinLosePacket(packet, 1, this);
		break;
	case CLIENT_SWITCH_STATION:
		unsigned int receivedStationType;
		packet >> receivedStationType;
		if(_ship->GetStation((StationType)receivedStationType)->setStationOccupation() == false)
			printf("Could not set station to occupied!\n");
		/* TODO: REIMPLEMENT WHEN NETWORKING AND PLAYERLISTS ARE FUNCTIONAL
		for(std::list<Player*>::iterator i=_playerList.begin(); i!=_playerList.end(); ++i)
		{			
			if((*i)->Ipadres == packet.GetSender().address.host)
			{
				unsigned int receivedStationType;
				packet >> receivedStationType;
				if(_ship->GetStation((StationType)receivedStationType)->setPlayerOccupation((*i)) == false)
					printf("Code is not handling stations correctly. This error originates in [GameScene.cpp] in function [HandleNetworkMessage].\n");
			}
		}*/
		break;
	case CLIENT_LEAVE_STATION:
		unsigned int receivedStation;
		packet >> receivedStation;
		_ship->GetStation((StationType)receivedStation)->resetStationOccupation();
		/* TODO: REIMPLEMENT WHEN NETWORKING AND PLAYERLISTS ARE FUNCTIONAL
		for(std::list<Player*>::iterator i=_playerList.begin(); i!=_playerList.end(); ++i)
		{			
			if((*i)->Ipadres == packet.GetSender().address.host)
			{
				unsigned int receivedStationType;
				packet >> receivedStationType;
				_ship->GetStation((StationType)receivedStationType)->resetPlayerOccupation();
			}
		}*/
		break;
	case CLIENT_FIRE_LASER:
		this->_laserPool->setAllObjects(SendAndReceivePackets::receiveLaserPacketFromClient(packet, this->_laserPool->getAllObjects(), this));
	}
}

void GameScene::switchStation(StationType type)
{
	_shipmap->disable();

	_ship->SwitchToStation(type);
}

void GameScene::handleShipMessage(ShipMessage message){
	if (message == LEAVESTATION){		
		_shipmap->enable();
	}
}

GameScene::~GameScene() 
{
	delete _laserPool;
}


