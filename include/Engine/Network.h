#ifndef NETWORK
#define NETWORK

#include <enet\enet.h>
#include <process.h>
#include <list>
#include <vector>
#include "SFML\System.hpp"
#include <exception>

// forward declare NetworkPacket to prevent circular dependancy
class NetworkPacket;
class INetworkListener;

/* IMPORTANT: before adding PacketTypes, read the following two pages:
* https://github.com/gametechnology/psi-2013/wiki/Packet-types-101
* https://github.com/gametechnology/psi-2013/wiki/PacketType-overview
*/
enum PacketType
{
	CLIENT_JOIN = 0,
	CLIENT_QUIT,
	ClIENT_IN_LOBBY,
	CLIENT_JOIN_DENIED,
	CLIENT_SHIP_MOVEMENT,

	HOST_DISCONNECT,
	START_GAME,
	SERVER_ENEMY,

	//player info
	CLIENT_UPDATE_PLAYER_DATA,
	CLIENT_ADD_PLAYER_DATA,
	CLIENT_REMOVE_PLAYER_DATA,
	JOIN_STATION,
	JOIN_STATION_ACCEPTED,
	JOIN_STATION_DENIED,

	//Add new PacketTypes above
	LAST_TYPE
};


inline char* getPacketTypeName(PacketType type)
{
	switch(type)
	{
		case CLIENT_JOIN: { return "CLIENT_JOIN"; break; }
		case CLIENT_QUIT: { return "CLIENT_QUIT"; break; }
		case ClIENT_IN_LOBBY: { return "ClIENT_IN_LOBBY"; break; }
		case CLIENT_JOIN_DENIED: { return "CLIENT_JOIN_DENIED"; break; }  
		case CLIENT_SHIP_MOVEMENT: { return "CLIENT_SHIP_MOVEMENT"; break; }
		case HOST_DISCONNECT: { return "HOST_DISCONNECT"; break; }
		case START_GAME: { return "START_GAME"; break; }
		case SERVER_ENEMY: { return "SERVER_ENEMY"; break; }

		case CLIENT_UPDATE_PLAYER_DATA: return "CLIENT_UPDATE_PLAYER_DATA";
		case CLIENT_ADD_PLAYER_DATA: return "CLIENT_ADD_PLAYER_DATA";
		case CLIENT_REMOVE_PLAYER_DATA: return "CLIENT_REMOVE_PLAYER_DATA";
		case JOIN_STATION: return "JOIN_STATION";
		case JOIN_STATION_ACCEPTED: return "JOIN_STATION_ACCEPTED";
		case JOIN_STATION_DENIED: return "JOIN_STATION_DENIED";

		default: { throw "Tried to get string from non-existing packet type"; }
	}
}

class Network
{
private:

	const int _port;

	static bool isInitialized;

	Network();
	void StartThreads();
	void StopThreads();
	void PacketReciever();
	void DistributePacket(NetworkPacket packet);
	unsigned int GeneratePacketTypesChecksum();

	sf::Thread* _receiverThread;
	sf::Mutex _mutex;
	
	bool _isServer;
	bool _isConnected;
	static Network* instance;
	std::list<INetworkListener*>* _listeners[LAST_TYPE];
	std::vector<NetworkPacket> _receivedPackets;
	ENetAddress _address;
	ENetHost* _host;
	ENetEvent _event;
	ENetPeer* _peer;
	unsigned int _packetTypeChecksum;

public:
	~Network();
	
	/*
	* Gets you an instance of the Network interface. If not initialized yet, it will then.
	*/
	static Network* GetInstance();

	/*
	* Initialize a client. When the connection with the server is succesfull, you will be able to send and receive messages.
	*/
	void InitializeClient(const char* ipAdress, unsigned int maxDownstream = 0, unsigned int maxUpstream = 0);

	/* 
	* Initialize a server. When succesfull, clients will be able to connect to you and receive your server messages.
	*/
	void InitializeServer(size_t maxPlayers = 16);

	/* 
	* Deinitialize as server or as client
	*/
	void DeInitialize();
	/*
	* Returns true if you are the server and the server is succesfully initialized.
	*/
	bool IsServer();

	/*
	* Returns true if you are a client or server and the network interface is succesfully initialized.
	*/
	bool IsConnected();

	/*
	* Sends a packet to the server. If you are the server, this messages will be send to yourself, as if another client sends
	* you this message.
	*/
	void SendPacket(NetworkPacket packet, const bool reliable = false);

	/*
	* If you are a server, sends a packet to all connected clients, including yourself, as if you are be a client.
	*/
	void SendServerPacket(NetworkPacket packet, const bool reliable = false);

	/*
	* Add a listener to the Network interface. If the Network interface receives a message of the specified PacketType
	* the listener's HandleNetworkMessage() will be called.
	*/
	void AddListener(PacketType packetType, INetworkListener* listener);

	/*
	* Removes a listener so it won't receive any packet anymore.
	*/
	void RemoveListener(INetworkListener* listener);

	/*
	* Removes a listener for the specified PacketType. The listener will still receive other PacketTypes.
	*/
	void RemoveListener(PacketType packetType, INetworkListener* listener);

	/*
	* Distributes all buffered packets that are received by the Network interface.
	*/
	void DistributeReceivedPackets();

	/*
	* Generates a checksum of the packet types enum. This comes in handy when checking if the server and client
	* have the same packet types.
	*/
	unsigned int GetPacketTypeChecksum();

	

};

#endif
