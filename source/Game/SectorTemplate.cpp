#include "SectorTemplate.h"
#include "SectorManager.h"

using namespace irr;
using namespace irr::core;

NetworkPacket packet(SERVER_ENEMY);

// Constructor
SectorTemplate::SectorTemplate(Core* core, SectorManager* sectormanager, std::string skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : Composite("SectorTemplate") 
{
	_core = core;
	_sectormanager = sectormanager;	
	_skyboxPath = skyBoxTexture;

	_fog = new Mist(_core);
	_boundry = boundryRadius;
	
	createWormHoles(amountWormHoles);

	if(!Network::GetInstance()->IsServer())
	{
		Network::GetInstance()->AddListener(SERVER_ENEMY, this);
	}

	_enemyList = std::vector<Enemy*>();
}

void SectorTemplate::init() 
{
	_core->getActiveScene()->addComponent(new Skybox(_core->getSmgr(), _core->getDriver(), _skyboxPath));
	addComponent(_fog );

	if(Network::GetInstance()->IsServer())
	{
		createEnemies();
		SendAndReceivePackets::sendEnemyPacket(_enemyList);
	}

	Composite::init();
}

// This function will create the wormholes needed for the current sector
void SectorTemplate::createWormHoles( unsigned int amountOfWormHoles ) {
	
	for(unsigned int i = 0; i < amountOfWormHoles; i++) 
	{
		vector3df* wormHolePos = new vector3df(1,0,0);

		wormHolePos->setLength((float)(rand() % int(_boundry* 0.2) + int(_boundry* 0.8)));

		_wormHoles.push_back(new BillboardComponent(_core->getSmgr(), wormHolePos, dimension2df(1, 1)));
		addComponent(_wormHoles[i]);
	}
}

int timer = 0;

void SectorTemplate::update()
{
	if( _sectormanager->getShip()->getPosition()->getLength() > _boundry ){
		printf("\n OUT OF BOUNDS!");
	}

	for(unsigned int i = 0; i < this->_wormHoles.size(); i++){
		irr::core::vector3df deltaPos = *_wormHoles[i]->getPosition() - *_sectormanager->getShip()->getPosition();
		float collisionRadius = 50;
		if( deltaPos.getLength() < collisionRadius ){			
			_sectormanager->handleMessage(NEXT_SECTOR,(void*)i );
			break;
		}
	}
	
	if(timer >= 50)
	{
		if(Network::GetInstance()->IsServer())
		{
			SendAndReceivePackets::sendEnemyPacket(_enemyList);
		}
		timer = 0;
	}
	// This is not seconds, what are you trying to do?
	timer++;
	
	Composite::update();
}

void SectorTemplate::handleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == SERVER_ENEMY)
	{
		_enemyList = SendAndReceivePackets::receiveEnemyPacket(packet, NULL, _enemyList);
	}
}

void SectorTemplate::createEnemies()
{
	int droneLimit = (rand() % 25);
	for(int i = 0; i < droneLimit; i++)
	{
			irr::core::vector3df pos = irr::core::vector3df((float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750));
			_enemyList.push_back(new EnemyDrone(_core->getSmgr() ,pos));
		
		addComponent(_enemyList.back());
	}
	int fighterLimit = (rand() % 15);
	for(int j = 2; j < fighterLimit; j++)
	{
		irr::core::vector3df pos = irr::core::vector3df((float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750));
		_enemyList.push_back(new EnemyFighter(_core->getSmgr(), pos));
		
		addComponent(_enemyList.back());
	}
}

SectorTemplate::~SectorTemplate() {
}
