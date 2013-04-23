#include "EnemySceneTest.h"

#include "Skybox.h"
#include "EnemyManager.h"
#include "RandomGenerator.h"


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

sf::Packet& operator <<(sf::Packet& out, irr::core::array<Enemy*>& in)
{
	out << in.size();
	for(unsigned i = 0; i < in.size(); i++)
	{
		out << *in[i];
	}
	return out;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::array<Enemy>& out)
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

NetworkPacket packet(ENEMY);

EnemySceneTest::EnemySceneTest(void)
{
	Network::GetInstance()->AddListener(ENEMY, this);
	Network::GetInstance()->AddListener(CLIENT_JOIN, this);
	EnemySceneTest::_enemyList = array<Enemy*>();
}


EnemySceneTest::~EnemySceneTest(void)
{
	Scene::~Scene();
}

void EnemySceneTest::HandleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == ENEMY)
	{
		if(!Network::GetInstance()->IsServer())
		{
			array<Enemy> serverEnemies = array<Enemy>();
			array<int> enemyIds = array<int>();

			packet >> serverEnemies;

			for(unsigned i = 0; i < serverEnemies.size(); i++)
			{
				enemyIds.push_back(serverEnemies[i].getId());
			}

			for(unsigned j = 0; j < _enemyList.size(); j++)
			{
				if(enemyIds.binary_search(_enemyList[j]->getId()) == -1)
				{
					_enemyList[j]->destroy();
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

					_enemyList.getLast()->setId(serverEnemies[i].getId());
					_enemyList.getLast()->setPosition(serverEnemies[i].getPosition());
					_enemyList.getLast()->setVelocity(serverEnemies[i].getVelocity());
					_enemyList.getLast()->setRotation(serverEnemies[i].getRotation());
				}
			}
		}
	}
}


void EnemySceneTest::init()
{
	//EnemyManager* enemymanager;
	smgr = Game::getSceneManager();
	camera = smgr->addCameraSceneNodeFPS();
	this->light = smgr->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
	//enemymanager = new EnemyManager();	
	//enemymanager->createEnemies();
	//addComponent(enemymanager);

	if(Network::GetInstance()->IsServer())
	{
		createEnemies();
	}
}

int timer = 0;

void EnemySceneTest::update()
{
	Scene::update();
	if(timer >= 500)
	{
		if(Network::GetInstance()->IsServer())
		{
			packet << _enemyList;
				_enemyList[i]->updateHealth();

			Network::GetInstance()->SendServerPacket(packet);
		}
		timer = 0;
	}
	timer++;
}


void EnemySceneTest::createEnemies()
{
	this->_enemyList = array<Enemy*>();

	for(int i = 0; i < 20; i++)
	{
		_enemyList.push_back(new EnemyDrone(irr::core::vector3df(0,0,(irr::f32)(i + (i * i)))));
		addComponent(_enemyList.getLast());
	}
}