#include "EnemySceneTest.h"

#include "Skybox.h"
#include "EnemyManager.h"
#include "RandomGenerator.h"
#include "EnemyPlayer.h"
///////////////////////////////////////////////////////////
//
//Not used scene, can be used for testing the enemy.
//
//////////////////////////////////////////////////////////

/*sf::Packet& operator <<(sf::Packet& out, Enemy& in)
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
}*/

//NetworkPacket packet(SERVER_ENEMY);

#include <iostream>

EnemySceneTest::EnemySceneTest(void) : Scene()
{
	Network::GetInstance()->AddListener(SERVER_ENEMY, this);
	EnemySceneTest::_enemyList = vector<Enemy*>();
	EnemyPlayer* player1 = new EnemyPlayer(irr::core::vector3df(0,1,0),irr::core::vector3df(0,0,0));
	addChild(player1);
	EnemyPlayer* player2 = new EnemyPlayer(irr::core::vector3df(20,1,0),irr::core::vector3df(-1,0,0));
	addChild(player2);
}

EnemySceneTest::~EnemySceneTest(void)
{
	Scene::~Scene();
}

void EnemySceneTest::HandleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == SERVER_ENEMY)
	{
		if(!Network::GetInstance()->IsServer())
		{
			vector<Enemy> serverEnemies = vector<Enemy>();

			//packet >> serverEnemies;

			for(unsigned j = 0; j < _enemyList.size(); j++)
			{
				for(unsigned k = 0; k < serverEnemies.size(); k++)
				{
					if(_enemyList[j]->getId() == serverEnemies[k].getId())
					{
						continue;
					}
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

void EnemySceneTest::init()
{
	Scene::init();
	this->game->device->getSceneManager()->addCameraSceneNodeFPS();
}

//int timer = 0;

void EnemySceneTest::update()
{
	Scene::update();

	/*if(timer >= 50)
	{
		if(Network::GetInstance()->IsServer())
		{
			packet.clear();
			//packet << _enemyList;

			Network::GetInstance()->SendServerPacket(packet);
		}
		timer = 0;
	}
	timer++;*/
}

void EnemySceneTest::onAdd()
{
	Scene::onAdd();

	/*if(Network::GetInstance()->IsServer())
	{
		createEnemies();

		packet.clear();
		//packet << _enemyList;

		Network::GetInstance()->SendServerPacket(packet);
	}*/

}


void EnemySceneTest::createEnemies()
{
	for(int i = 0; i < 20; i++)
	{
		_enemyList.push_back(new EnemyDrone(irr::core::vector3df(0,0,(irr::f32)(i + (i * i)))));
		
		addChild(_enemyList.back());
	}

	for(int j = 2; j < 10; j++)
	{
		_enemyList.push_back(new EnemyFighter(irr::core::vector3df(0,(irr::f32)(j + (j * j)),0)));
		
		addChild(_enemyList.back());
	}

	for(int k = 2; k < 30; k++)
	{
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df((irr::f32)(k + (k * k)),0,0), irr::core::vector3df(0,0,0.01f)));
		
		addChild(_enemyList.back());
	}

	_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(-10,0,0), irr::core::vector3df(0.02f,0,0)));
	addChild(_enemyList.back());

	//_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(10,0,0), irr::core::vector3df(-0.02f,0,0)));
	//addChild(_enemyList.back());
}