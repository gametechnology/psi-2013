#include "SendAndReceivePackets.h"
#include "Laser.h"


Core* SendAndReceivePackets::core;

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
		std::vector<Enemy> serverEnemies = std::vector<Enemy>();

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
				delete enemy;
			}
		}

		for(unsigned i = 0; i < serverEnemies.size(); i++)
		{
			for(unsigned j = 0; j < enemyList.size(); j++)
			{
				if(enemyList[j]->getId() == serverEnemies[i].getId())
				{
					enemyList[j]->setPosition(*serverEnemies[i].getPosition());
					enemyList[j]->setVelocity(serverEnemies[i].getVelocity());
					enemyList[j]->setRotation(*serverEnemies[i].getRotation());
					continue;
				}
			}
			if(serverEnemies.size() > enemyList.size())
			{
				switch(serverEnemies[i].getType())
				{
				case Enemy::ASTROID:
					enemyList.push_back(new EnemyAsteroid(core->getSmgr(), *serverEnemies[i].getPosition(), *serverEnemies[i].getVelocity()));
					break;
				case Enemy::DRONE:
					enemyList.push_back(new EnemyDrone(core->getSmgr(), *serverEnemies[i].getPosition()));
					break;
				case Enemy::FIGHTER:
					enemyList.push_back(new EnemyFighter(core->getSmgr(), *serverEnemies[i].getPosition()));
					break;
				}

				enemyList.back()->setId(serverEnemies[i].getId());
				enemyList.back()->setPosition(*serverEnemies[i].getPosition());
				enemyList.back()->setVelocity(serverEnemies[i].getVelocity());
				enemyList.back()->setRotation(*serverEnemies[i].getRotation());
				scene->addComponent(enemyList.back());
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

/*TODO:
Make sure the laser is only visible on the right sector, currently shows all the lasers that er enabled
*/
std::vector<Laser*> SendAndReceivePackets::receiveLaserPacket(NetworkPacket& packet, std::vector<Laser*> laserList, Scene* scene)
{
	std::vector<Laser> serverList;
	packet >> serverList;

	for(unsigned i = 0; i < serverList.size(); i++)
	{
		for(unsigned j = 0; j < laserList.size(); j++)
		{
			if(serverList[i].getId() == laserList[j]->getId())
			{
				if(laserList[j]->getScene() != scene)
				{
					laserList[j]->getScene()->removeComponent(laserList[j]);
					scene->addComponent(laserList[j]);
				}

				if(serverList[i].isEnabled())
					laserList[j]->setEnabled(true);
				else
				{
					laserList[j]->setEnabled(false);
					laserList[j]->update();
				}

				laserList[j]->setPosition(*serverList[i].getPosition());
				laserList[j]->setVelocity(serverList[i].getVelocity());
				laserList[j]->setRotation(*serverList[i].getRotation());

			}
		}
	}
	return laserList;
}

std::vector<Laser*> SendAndReceivePackets::receiveLaserPacketFromClient(NetworkPacket& packet, std::vector<Laser*> laserList, Scene* scene, irr::scene::ISceneManager* smgr)
{
	Laser clientLaser = Laser(smgr);
	packet >> clientLaser;
	for(unsigned j = 0; j < laserList.size(); j++)
	{
		if(clientLaser.getId() == laserList[j]->getId())
		{
			if(laserList[j]->getScene() != scene)
			{
				// This will crash. If the active Laser Scene is not the current scene of the client
				// it will mean that that scene does not exist for this client
				// so removing components of that scene will result in a null pointer.
				laserList[j]->getScene()->removeComponent(laserList[j]);
				scene->addComponent(laserList[j]);
			}

			if(clientLaser.isEnabled())
				laserList[j]->setEnabled(true);
			else
			{
				laserList[j]->setEnabled(false);
				laserList[j]->update();
			}

			laserList[j]->setPosition(*clientLaser.getPosition());
			laserList[j]->setVelocity(clientLaser.getVelocity());
			laserList[j]->setRotation(*clientLaser.getRotation());
		}
	}

	return laserList;
}

void SendAndReceivePackets::sendWinLosePacket(int LosingteamId)
{
	NetworkPacket packet(SERVER_WINLOSE);
	packet << LosingteamId;
	sendServerPacket(packet, true);
}

void SendAndReceivePackets::receiveWinLosePacket(NetworkPacket& packet, int teamId, Scene* currentScene)
{
	int team;
	packet >> team;

	SendAndReceivePackets::handleWinLose(team, teamId, currentScene);
}

void SendAndReceivePackets::handleWinLose(int losingTeam, int teamId, Scene* currentScene)
{
	if(losingTeam == teamId)
	{
		currentScene->requestNextScene();
	}else
	{
		currentScene->requestNextScene();
	}
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
	out.setVelocity(&velocity);
	out.setRotation(rotation);

	return in;
}

sf::Packet& operator <<(sf::Packet& out, std::vector<Enemy*>& in)
{
	out << in.size();
	for(unsigned i = 0; i < in.size(); i++)
	{
		out << *in[i];
	}
	return out;
}



sf::Packet& operator >>(sf::Packet& in, std::vector<Enemy>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		Enemy* enemy = new Enemy();
		in >> *enemy;
		out.push_back(*enemy);
	}
	return in;
}

sf::Packet& operator <<(sf::Packet& out, Laser& in)
{
	return out << in.getId() << in.isEnabled() << *in.getPosition() << *in.getVelocity() << *in.getRotation();
}

sf::Packet& operator >>(sf::Packet& in, Laser& out)
{
	bool enabled;
	irr::core::vector3df position;
	irr::core::vector3df velocity;
	irr::core::vector3df rotation;

	int id;

	in >> id >> enabled >> position >> velocity >> rotation;

	out.setId(id);
	if(enabled)
	{
		out.setEnabled(true);
	}else
	{
		out.setEnabled(false);
		out.update();
	}

	out.setPosition(position);
	out.setVelocity(&velocity);
	out.setRotation(rotation);

	return in;
}

sf::Packet& operator <<(sf::Packet& out, std::vector<Laser*>& in)
{
	out << in.size();
	for(unsigned int i = 0; i < in.size(); i++)
	{
		out << *in[i];
	}
	return out;
}

Laser laser;

sf::Packet& operator >>(sf::Packet& in, std::vector<Laser>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		in >> laser;
		out.push_back(laser);
	}
	return in;
}