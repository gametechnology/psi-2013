#include "SendAndReceivePackets.h"

void SendAndReceivePackets::sendPacket(NetworkPacket packet, const bool reliable)
{
	Network::GetInstance()->SendPacket(packet, reliable);
}

void SendAndReceivePackets::sendServerPacket(NetworkPacket packet, const bool reliable)
{
	if(Network::GetInstance()->IsServer())
	{
		Network::GetInstance()->SendServerPacket(packet, reliable);
	}
}

void SendAndReceivePackets::sendEnemyPacket(std::vector<Enemy*> enemyList, const bool reliable)
{
	NetworkPacket packet(SERVER_ENEMY);
	packet << enemyList;
	sendServerPacket(packet, reliable);
}

std::vector<Enemy*> SendAndReceivePackets::receiveEnemyPacket(NetworkPacket& packet, Scene* scene, 
	std::vector<Enemy*> enemyList)
{
	if(!Network::GetInstance()->IsServer())
	{
		vector<Enemy> serverEnemies = vector<Enemy>();

		packet >> serverEnemies;


		for(unsigned j = 0; j < enemyList.size(); j++)
		{
			bool isAtServer = false;
			for(unsigned k = 0; k < serverEnemies.size(); k++)
			{
				if(enemyList[j]->getId() == serverEnemies[k].getId())
				{
					isAtServer = true;
				}
			}
				
			if(!isAtServer)
			{
				Enemy* enemy = enemyList[j];
				enemyList.erase(enemyList.begin() + j);
				enemy->destroy();
			}
		}

		for(unsigned i = 0; i < serverEnemies.size(); i++)
		{
			for(unsigned j = 0; j < enemyList.size(); j++)
			{
				if(enemyList[j]->getId() == serverEnemies[i].getId())
				{
					enemyList[j]->setPosition(serverEnemies[i].getPosition());
					enemyList[j]->setVelocity(serverEnemies[i].getVelocity());
					enemyList[j]->setRotation(serverEnemies[i].getRotation());
					continue;
				}
			}
			if(serverEnemies.size() > enemyList.size())
			{
				switch(serverEnemies[i].getType())
				{
				case Enemy::ASTROID:
					enemyList.push_back(new EnemyAsteroid(serverEnemies[i].getPosition(), serverEnemies[i].getVelocity()));
					break;
				case Enemy::DRONE:
					enemyList.push_back(new EnemyDrone(serverEnemies[i].getPosition()));
					break;
				case Enemy::FIGHTER:
					enemyList.push_back(new EnemyFighter(serverEnemies[i].getPosition()));
					break;
				}

				enemyList.back()->setId(serverEnemies[i].getId());
				enemyList.back()->setPosition(serverEnemies[i].getPosition());
				enemyList.back()->setVelocity(serverEnemies[i].getVelocity());
				enemyList.back()->setRotation(serverEnemies[i].getRotation());
				scene->addChild(enemyList.back());
			}
		}
	}
	return enemyList;
}

void SendAndReceivePackets::sendLazerPacket(std::vector<Laser*> laserList, const bool reliable)
{
	NetworkPacket packet(SERVER_LASER);
	packet << laserList;
	sendServerPacket(packet, reliable);
}

std::vector<Laser*> SendAndReceivePackets::receiveLaserPacket(NetworkPacket& packet, std::vector<Laser*> laserList)
{
	return laserList;
}

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

sf::Packet& operator <<(sf::Packet& out, Laser& in)
{
	return out << in.getId() << in.scene << in.transform->position << in.transform->velocity << in.transform->rotation;
}

sf::Packet& operator >>(sf::Packet& in, Laser& out)
{
	int id;
	Scene* scene;
	irr::core::vector3df position;
	irr::core::vector3df velocity;
	irr::core::vector3df rotation;

	in >> id >> scene >> position >> velocity >> rotation;

	out.setId(id);
	out.scene = scene;
	*out.transform->position = position;
	*out.transform->velocity = velocity;
	*out.transform->rotation = rotation;

	return in;
}

sf::Packet& operator <<(sf::Packet& out, std::vector<Laser*>& in)
{
	out << in.size();
	for(int i = 0; i < in.size(); i++)
	{
		out << *in[i];
	}
	return out;
}

sf::Packet& operator >>(sf::Packet& in, std::vector<Laser>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		Laser laser;
		in >> laser;
		out.push_back(laser);
	}
	return in;
}

sf::Packet& operator <<(sf::Packet& out, Scene* in)
{
	//edit this if more is needed to send a scene over
	return out << in->game->sceneManager->getNameScene(in)->name;
}

sf::Packet& operator >>(sf::Packet& in, Scene* out)
{
	char* sceneName;
	in >> sceneName;

	//the scene you currently send with needs the game so if you make a temporarely scene set the game
	if(out->game != NULL)
	{
		out = out->game->sceneManager->getScene(sceneName);
	}

	return in;
}
