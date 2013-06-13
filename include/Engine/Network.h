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
		SHIP_ACCELERATION,
		SERVER_LASER,
		SERVER_WINLOSE,
		SERVER_POWER_CHANGED,
		SERVER_SWITCH_STATION,
		SERVER_LEAVE_STATION,

        CLIENT_SWITCH_STATION,
        CLIENT_LEAVE_STATION,
        CLIENT_POWER_CHANGED,
        CLIENT_HEALTH_CHANGED,
		CLIENT_FIRE_LASER,
        SERVER_ALL_PLAYERS,
        CLIENT_GET_ALL_PLAYERS,
 
		//switch station packets
		CLIENT_REQUEST_ENTER_STATION,
		SERVER_ENTER_STATION_ACCEPTED,
		SERVER_ENTER_STATION_DENIED,
		
        SERVER_JOIN_DENIED,
        SERVER_LOBBY_STATUS,

 
        //these are packages handled by the playerManager
        CLIENT_REQUEST_JOIN_SERVER,
        CLIENT_UPDATE_STATUS,
		SERVER_UPDATE_STATUS,

        SERVER_REQUEST_ACCEPTED,
        SERVER_REQUEST_DENIED, 
        

		SERVER_PONG,
		CLIENT_PING,
		SERVER_DISCONNECTED,
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
				case SHIP_ACCELERATION: { return "SHIP_ACCELERATION"; break; }
				case SERVER_LASER: { return "SERVER_LASER"; break; }
				case SERVER_WINLOSE: { return "SERVER_WINLOSE"; break; }
 
				case SERVER_POWER_CHANGED: { return "SERVER_POWER_CHANGED"; break; }
				case SERVER_SWITCH_STATION: { return "SERVER_SWITCH_STATION"; break; }
				case SERVER_LEAVE_STATION: { return "SERVER_LEAVE_STATION"; break; }
	
                case CLIENT_SWITCH_STATION: { return "CLIENT_SWITCH_STATION"; break; }
                case CLIENT_LEAVE_STATION: { return "CLIENT_LEAVE_STATION"; break; }
                case CLIENT_POWER_CHANGED: { return "CLIENT_POWER_CHANGED"; break; }
                case CLIENT_HEALTH_CHANGED: { return "CLIENT_HEALTH_CHANGED"; break; }
				case CLIENT_FIRE_LASER: { return "CLIENT_FIRE_LASER"; break; }

				case CLIENT_REQUEST_ENTER_STATION: { return "CLIENT_REQUEST_ENTER_STATION"; }
				case SERVER_ENTER_STATION_ACCEPTED: { return "CLIENT_UPDATE_STATUS"; }
				case SERVER_ENTER_STATION_DENIED: { return "SERVER_ENTER_STATION_DENIED"; }

                case SERVER_ALL_PLAYERS: {return "SERVER_ALL_PLAYERS"; break;}
                case CLIENT_GET_ALL_PLAYERS: {return "CLIENT_GET_ALL_PLAYERS"; break;}
 
                case SERVER_JOIN_DENIED: { return "SERVER_JOIN_DENIED"; break; }
                case SERVER_LOBBY_STATUS: {return "SERVER_LOBBY_STATUS"; break;}
 
                case CLIENT_REQUEST_JOIN_SERVER: { return "CLIENT_REQUEST_JOIN_SERVER"; break;}

                case CLIENT_UPDATE_STATUS: { return "CLIENT_UPDATE_STATUS"; break;}
				case SERVER_UPDATE_STATUS: { return "SERVER_UPDATE_STATUS"; break; }
 
                case SERVER_REQUEST_ACCEPTED: { return "SERVER_REQUEST_ACCEPTED"; break; }
                case SERVER_REQUEST_DENIED: { return "SERVER_REQUEST_DENIED"; break; }
                
				
				case SERVER_PONG: { return "SERVER_PONG"; break; }
				case CLIENT_PING: { return "CLIENT_PING"; break; }
				case SERVER_DISCONNECTED: { return "SERVER_DISCONNECTED"; break; }
				
                default: { throw "Tried to get string from non-existing packet type"; }
        }
}

class Network
{
private:

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
	NetworkPacket AddSendAll(NetworkPacket packet, bool sendall);

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

	const enet_uint32 GetLocalAddress();

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


	void SendPacketToAllClients(NetworkPacket packet, const bool reliable = false);

	
	/*
	* If you are a server, sends a packet to all connected clients, including yourself, as if you are be a client.
	*/
	void SendServerPacket(NetworkPacket packet, const bool reliable = false);

	/*
	* If you are a server, sends a packet to a specific client
	*/
	void SendServerPacket(NetworkPacket packet, ENetPeer* peer, const bool reliable);

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
