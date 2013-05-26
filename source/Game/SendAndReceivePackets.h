#ifndef SEND_AND_RECEIVE_PACKETS_H
#define SEND_AND_RECEIVE_PACKETS_H

#include "NetworkInterface.h"
#include "Engine\Scene.h"
#include "Enemy.h"
#include "EnemyAsteroid.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "Laser.h"
#include "Engine\Scene.h"
#include "EndScene.h"

static class SendAndReceivePackets
{
public:

	static Game* staticGame;
	//sends a packet to the server
	static void sendPacket(NetworkPacket packet, const bool reliable = false);

	//sends a packet from the server to it's clients
	static void sendServerPacket(NetworkPacket packet, const bool reliable = false);

	//send and receives enemy packets
	static void sendEnemyPacket(std::vector<Enemy*> enemyList, const bool relibale = false);
	static std::vector<Enemy*> receiveEnemyPacket(NetworkPacket& packet, Scene* scene, std::vector<Enemy*> enemyList);

	//send and receive laser packets
	static void sendLazerPacket(std::vector<Laser*> laserList, const bool reliable = false);
	static std::vector<Laser*> receiveLaserPacket(NetworkPacket& packet, std::vector<Laser*> laserList, Scene* scene);
	static std::vector<Laser*> SendAndReceivePackets::receiveLaserPacketFromClient(NetworkPacket& packet, std::vector<Laser*> laserList, Scene* scene);

	static void sendWinLosePacket(int LosingteamId);
	static void receiveWinLosePacket(NetworkPacket& packet, int teamId, Scene* currentScene);
	static void handleWinLose(int losingTeam, int teamID, Scene* currentScene);


	friend sf::Packet& operator <<(sf::Packet& out, Enemy& in);
	friend sf::Packet& operator >>(sf::Packet& in, Enemy& out);
	friend sf::Packet& operator <<(sf::Packet& out, vector<Enemy*>& in);
	friend sf::Packet& operator >>(sf::Packet& in, vector<Enemy>& out);

	friend sf::Packet& operator <<(sf::Packet& out, Laser& in);
	friend sf::Packet& operator >>(sf::Packet& in, Laser& out);
	friend sf::Packet& operator <<(sf::Packet& out, vector<Laser*>& in);
	friend sf::Packet& operator >>(sf::Packet& in, vector<Laser>& out);
};

#endif