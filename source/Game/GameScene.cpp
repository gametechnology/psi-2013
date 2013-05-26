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
}

void GameScene::onAdd() {
	SendAndReceivePackets::staticGame = this->game;
	Network::GetInstance()->AddListener(SERVER_LASER, this);
	Network::GetInstance()->AddListener(SERVER_WINLOSE, this);

	this->_sendLasersTimer = 0;
	this->_laserPool = new ObjectPool<Laser>(*this, 100);
	EnemyFighter::laserPool = _laserPool;
	Ship::laserPool = _laserPool;

	_ship = new Ship(vector3df(0,0,0), vector3df(0,0,0));
	addChild(_ship);

	_camera = new Camera(); 
	_ship->addChild(_camera);
	_camera->init();

	_shipEnemy = new Ship(vector3df(0,0,-100), vector3df(180,0,0));
	addChild(_shipEnemy);

	BasicMoverComponent* movComp = new BasicMoverComponent();
	_shipEnemy->addComponent(movComp);

	//Creates Map & SectorManager
	GalaxyMap* galaxyMap = new GalaxyMap(300, 300, 15);

	if (!testMap) {
		galaxyMap->createMap(20, 2, 5);
	} else {
		galaxyMap->createStaticMap();
	}
	galaxyMap->transform->position = new vector3df(100, 670, 0);
	printf("-----------Added SectorManager----------\n\n");
	addComponent(new SectorManager(galaxyMap,_ship));

	_shipmap = new Shipmap(this);
	addChild(_shipmap);

}

void GameScene::init() {
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
		/*
		TODO:
		Edit code below to make it send a winlose packet when one of the ship reaches health of 0
		and give the right team id as the parameter
		*/
		if(this->game->input->isKeyboardButtonPressed(KEY_KEY_Z) || this->_ship->getShipHealth() <= 0 || this->_shipEnemy->getShipHealth() <= 0)
		{
			SendAndReceivePackets::sendWinLosePacket(1);
			SendAndReceivePackets::handleWinLose(1, 2, this);
		}
	}

	Scene::update();
}

void GameScene::HandleNetworkMessage(NetworkPacket packet)
{
	std::cout<< packet.GetType() << endl;
	if(packet.GetType() == SERVER_LASER)
	{
		this->_laserPool->setAllObjects(SendAndReceivePackets::receiveLaserPacket(packet, this->_laserPool->getAllObjects(), this));
	}
	if(packet.GetType() == SERVER_WINLOSE)
	{
		SendAndReceivePackets::receiveWinLosePacket(packet, 1, this);
	}
	// TODO fix the packet data so it actually holds the ip adress of the sender.
	if(packet.GetType() == PacketType::CLIENT_SWITCH_STATION)
	{
		for(std::list<Player*>::iterator i=_playerList.begin(); i!=_playerList.end(); ++i)
		{
		}
	}
	if(packet.GetType() == CLIENT_FIRE_LASER)
	{
		this->_laserPool->setAllObjects(SendAndReceivePackets::receiveLaserPacketFromClient(packet, this->_laserPool->getAllObjects(), this));
	}
}

void GameScene::switchStation(StationType type)
{
	this->removeChild(_shipmap);

	_ship->SwitchToStation(type);
}

GameScene::~GameScene() 
{
	delete _laserPool;
}
