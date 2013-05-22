#include "GameScene.h"
#include "MapGenerator.h"
#include "SectorManager.h"
#include "Shipmap.h"
#include "SendAndReceivePackets.h"

GameScene::GameScene() : Scene() {

}

void GameScene::onAdd() {

	SendAndReceivePackets::staticGame = this->game;
	Network::GetInstance()->AddListener(SERVER_LASER, this);
	Network::GetInstance()->AddListener(SERVER_WINLOSE, this);

	this->_sendLasersTimer = 0;
	this->_laserPool = new ObjectPool<Laser>(50);
	EnemyFighter::laserPool = *_laserPool;
	GalaxyMap* galaxyMap = new GalaxyMap(300, 300, 15);
	
	galaxyMap->createMap(20, 2, 5);
	galaxyMap->transform->position = new vector3df(100, 670, 0);
	printf("-----------Added SectorManager----------\n\n");
	addComponent(new SectorManager(galaxyMap));

	_shipmap = new Shipmap(this);
	//addChild(_shipmap);

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
	}

	Scene::update();
}

void GameScene::HandleNetworkMessage(NetworkPacket packet)
{
	std::cout<< packet.GetType() << endl;
	if(packet.GetType() == SERVER_LASER)
	{
		this->_laserPool->setAllObjects(SendAndReceivePackets::receiveLaserPacket(packet, this->_laserPool->getAllObjects()));
	}
	if(packet.GetType() == SERVER_WINLOSE)
	{
		SendAndReceivePackets::receiveWinLosePacket(packet, 1, this);
	}
}

void GameScene::switchStation(StationType type)
{
	this->removeChild(_shipmap);

	switch(type)
	{
		case ST_DEFENCE:
			break;
		case ST_HELM:
			break;
		case ST_NAVIGATION:
			break;
		case ST_POWER:
			break;
		case ST_WEAPON:
			break;
	}
}

GameScene::~GameScene() {

}
