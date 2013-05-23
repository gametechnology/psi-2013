#include "GameScene.h"
#include "MapGenerator.h"
#include "SectorManager.h"
#include "Shipmap.h"

GameScene::GameScene(std::list<Player*> playerList, bool isTestMap) : Scene()
{
	this->testMap = isTestMap;
	_playerList = playerList;
	Network::GetInstance()->AddListener(CLIENT_SWITCH_STATION, this);
}

void GameScene::onAdd() {
	// The player
	_ship = new Ship(vector3df(0,0,-100), vector3df(0,0,0));

	_player = new Camera(); //TODO: Make the camera work correctly according to station
	

	_ship2 = new Ship(vector3df(0,0,-100), vector3df(180,0,0));
	addChild(_ship);
	_ship->addChild(_player);
	//TODO: Disabled this Caused errors 
	//_player->setTarget(vector3df(0, 0, -100));
	//_player->setUpVector(*_ship->transform->position);

	ShipMover* mover = new ShipMover(_ship);
	_ship->addComponent(mover);

	addChild(_ship2);

	BasicMoverComponent* movComp = new BasicMoverComponent();
	movComp->thrust = 0.01f;
	_ship2->addComponent(movComp);

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
	Scene::update();
}

void GameScene::switchStation(StationType type)
{
	this->removeChild(_shipmap);

	_ship->SwitchToStation(type);
}

void GameScene::HandleNetworkMessage(NetworkPacket packet)
{
	// TODO fix the packet data so it actually holds the ip adress of the sender.
	if(packet.GetType() == PacketType::CLIENT_SWITCH_STATION)
	{
		for(std::list<Player*>::iterator i=_playerList.begin(); i!=_playerList.end(); ++i)
		{
		}
	}
}

GameScene::~GameScene() {

}
