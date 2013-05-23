#include "SectorTemplate.h"
#include "Engine/Camera.h"
#include "Skybox.h"
#include "SectorManager.h"

sf::Packet& operator <<(sf::Packet& out, Enemy& in)
{
	return out << in.getId() << in.getType() << in.getPosition() << in.getVelocity() << in.getRotation();
}

sf::Packet& operator >>(sf::Packet& in, Enemy& out)
{
	int id;
	int type;
	irr::core::vector3df position;
	irr::core::vector3df velocity;
	irr::core::vector3df rotation;

	in >> id >> type >> position >> velocity >> rotation;

	out.setId(id);
	out.setType((Enemy::EnemyType)type);
	out.setPosition(position);
	out.setVelocity(velocity);
	out.setRotation(rotation);

	return in;
}

sf::Packet& operator <<(sf::Packet& out, vector<Enemy*>& in)
{
	out << in.size();
	for(unsigned i = 0; i < in.size(); i++)
	{
		out << *in[i];
	}
	return out;
}

sf::Packet& operator >>(sf::Packet& in, vector<Enemy>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		Enemy enemy;
		in >> enemy;
		out.push_back(enemy);
	}
	return in;
}

NetworkPacket packet(SERVER_ENEMY);

// Constructor
SectorTemplate::SectorTemplate(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : Scene() {
	//setting sector Manager
	_sectormanager = sectormanager;
	
	// Creating Skybox
	_skybox = new Skybox( skyBoxTexture );

	// Adding mist
	_fog = new Mist();
	
	// Setting the boundry
	_boundry = boundryRadius;

	
	// Creating wormholes
	createWormHoles( amountWormHoles );

	if(!Network::GetInstance()->IsServer())
	{
		Network::GetInstance()->AddListener(SERVER_ENEMY, this);
	}

	_enemyList = vector<Enemy*>();
}

void SectorTemplate::onAdd() {
	//this->_camera = this->getIrrlichtSceneManager()->addCameraSceneNodeFPS();
	//addComponent(_enemyManager);
	addChild( _skybox );
	addChild(_fog );

	// adding the wormholes
	addWormHoles();



	if(Network::GetInstance()->IsServer())
	{
		createEnemies();

		packet.clear();
		packet << _enemyList;

		Network::GetInstance()->SendServerPacket(packet);
	}

	Scene::onAdd();
}

//This function isn't being overriden so it needs to be called in constructor
void SectorTemplate::init(){
	Scene::init();
}

void SectorTemplate::createWormHoles( unsigned int amountOfWormHoles ) {
	//printf("[SectorTemplate] -=*[Begin of Create WormHole]*=- \n");
	//printf("[SectorTemplate] -=*[Amount of wormholes %i]*=- \n", amountOfWormHoles);
	
	for(unsigned int i = 0; i < amountOfWormHoles; i++) {
		// Creating a wormhole and giving it the pos we just calculated
		wormHole = new WormHole(i);
		
		// Pushing to the wormhole list
		this->_wormHoles.push_back( wormHole );
	}

	int size = _wormHoles.size();
	
	//printf("[SectorTemplate] -=*[Size array %i ]*=- \n" , size);
	//printf("[SectorTemplate] -=*[End of Create WormHole]*=- \n");
}

void SectorTemplate::addWormHoles() {
	printf("[SectorTemplate] -=*[Begin of Add WormHole]*=- \n");
	for(unsigned int i = 0; i < _wormHoles.size(); i++) {
		// Calculating the pos in the sector
		irr::core::vector3df wormHolePos((float)(rand() % int(_boundry*2) - int(_boundry)), (float)(rand() % int(_boundry*2) - int(_boundry)), (float)(rand() % int(_boundry*2) - int(_boundry)));
		
		// Making sure that the wormhole isn't spawned between 0% and 80% from the zero point to the radius of the sector
		wormHolePos.setLength((float)(rand() % int(_boundry* 0.2) + int(_boundry* 0.8)));

		// Adding the worm holes to the scene
		addChild(_wormHoles[i]);

		// And give it their position
		*_wormHoles[i]->transform->position = wormHolePos;
		printf("[SectorTemplate] wormhole.x[ %f ] wormhole.y[ %f ] wormhole.z[ %f ] \n",_wormHoles[i]->transform->position->X,_wormHoles[i]->transform->position->Y,_wormHoles[i]->transform->position->Z);
	}
	printf("[SectorTemplate] -=*[End of add WormHole]*=- \n");
}

int timer = 0;

void SectorTemplate::update(){
	/* Original when player is done
	// Checking if the player isn't going out side of the radius of the sector
	if( this->_player->position.getLength() > _boundry ){
		this->_player->handleMessage(OUT_OF_BOUNDS, NULL);
	}

	// Checking for collision with a wormhole
	for(unsigned int i = 0; i < this->_wormHoles.size(); i++){
		irr::core::vector3df deltaPos = _wormHoles[i]->position - this->_player->position;
		if( deltaPos.getLength() < 10 ){			
			_sectormanager->handleMessage(NEXT_SECTOR,(void*)i );
			break;
		}
	}
	*/

	// Placeholder because there is no player yet
	/*To use Fps camera:
	replace:
	this->_player->transform->position
	with
	this->_camera->getPosition()*/
	if( _sectormanager->getShip()->transform->position->getLength() > _boundry ){
		//printf("\n OUT OF BOUNDS!");
	}
	for(unsigned int i = 0; i < this->_wormHoles.size(); i++){
		irr::core::vector3df deltaPos = *_wormHoles[i]->transform->position - *_sectormanager->getShip()->transform->position;
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
			packet.clear();
			packet << _enemyList;

			Network::GetInstance()->SendServerPacket(packet);
		}
		timer = 0;
	}
	timer++;
	
	Scene::update();
}

void SectorTemplate::HandleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == SERVER_ENEMY)
	{
		if(!Network::GetInstance()->IsServer())
		{
			vector<Enemy> serverEnemies = vector<Enemy>();

			packet >> serverEnemies;


			for(unsigned int j = 0; j < _enemyList.size(); j++)
			{
				bool isAtServer = false;
				for(unsigned k = 0; k < serverEnemies.size(); k++)
				{
					if(_enemyList[j]->getId() == serverEnemies[k].getId())
					{
						isAtServer = true;
					}
				}
				
				if(!isAtServer)
				{
					Enemy* enemy = _enemyList[j];
					_enemyList.erase(_enemyList.begin() + j);
					enemy->destroy();
				}
			}

			for(unsigned i = 0; i < serverEnemies.size(); i++)
			{
				for(unsigned j = 0; j < _enemyList.size(); j++)
				{
					if(_enemyList[j]->getId() == serverEnemies[i].getId())
					{
						_enemyList[j]->setPosition(serverEnemies[i].getPosition());
						_enemyList[j]->setVelocity(serverEnemies[i].getVelocity());
						_enemyList[j]->setRotation(serverEnemies[i].getRotation());
						continue;
					}
				}
				if(serverEnemies.size() > _enemyList.size())
				{
					switch(serverEnemies[i].getType())
					{
					case Enemy::ASTROID:
						_enemyList.push_back(new EnemyAsteroid(serverEnemies[i].getPosition(), serverEnemies[i].getVelocity()));
						break;
					case Enemy::DRONE:
						_enemyList.push_back(new EnemyDrone(serverEnemies[i].getPosition()));
						break;
					case Enemy::FIGHTER:
						_enemyList.push_back(new EnemyFighter(serverEnemies[i].getPosition()));
						break;
					}

					_enemyList.back()->setId(serverEnemies[i].getId());
					_enemyList.back()->setPosition(serverEnemies[i].getPosition());
					_enemyList.back()->setVelocity(serverEnemies[i].getVelocity());
					_enemyList.back()->setRotation(serverEnemies[i].getRotation());
					this->addChild(_enemyList.back());
				}
			}
		}
	}
}

/////////////////////////////////////////////////////
//creating enemies, in further sprints they can be moved to the correct sector
void SectorTemplate::createEnemies()
{
	int droneLimit = (rand() % 25);
	for(int i = 0; i < droneLimit; i++)
	{
			irr::core::vector3df pos = irr::core::vector3df((float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750));
			_enemyList.push_back(new EnemyDrone(pos));
		
		addChild(_enemyList.back());
	}
	int fighterLimit = (rand() % 15);
	for(int j = 2; j < fighterLimit; j++)
	{
		irr::core::vector3df pos = irr::core::vector3df((float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750));
		_enemyList.push_back(new EnemyFighter(pos));
		
		addChild(_enemyList.back());
	}

	//for(int k = 2; k < 30; k++)
	//{
	//	_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df((irr::f32)(k + (k * k)),0,0), irr::core::vector3df(0,0,0.01f)));
	//	
	//	addChild(_enemyList.back());
	//}
	//
	//_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(-10,0,0), irr::core::vector3df(0.02f,0,0)));
	//addChild(_enemyList.back());

	//_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(10,0,0), irr::core::vector3df(-0.02f,0,0)));
	//addChild(_enemyList.back());
}

//void SectorTemplate::handleMessage(unsigned int message, void* data) {
//	
//	delete data;
//}

SectorTemplate::~SectorTemplate() {
	//_camera->drop();
	Scene::~Scene();
}
