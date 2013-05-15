#ifndef SEND_AND_RECEIVE_PACKETS_H
#define SEND_AND_RECEIVE_PACKETS_H

#include "NetworkInterface.h"
#include "Engine\Scene.h"
#include "Enemy.h"
#include "EnemyAsteroid.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"

static class SendAndReceivePackets
{
public:
	//sends a packet to the server
	static void sendPacket(NetworkPacket packet, const bool reliable = false);

	//sends a packet from the server to it's clients
	static void sendServerPacket(NetworkPacket packet, const bool reliable = false);

	//send and receives enemy packets
	static void sendEnemyPacket(std::vector<Enemy*> enemyList, const bool relibale = false);
	static void receiveEnemyPacket(NetworkPacket& packet, Scene* scene, std::vector<Enemy*>& enemyList);


	friend sf::Packet& operator <<(sf::Packet& out, Enemy& in);
	friend sf::Packet& operator >>(sf::Packet& in, Enemy& out);
	friend sf::Packet& operator <<(sf::Packet& out, vector<Enemy*>& in);
	friend sf::Packet& operator >>(sf::Packet& in, vector<Enemy>& out);
};

#endif