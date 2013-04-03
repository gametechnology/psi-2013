#ifndef NETWORKABLE
#define NETWORKABLE

#include <enet\enet.h>
#include <string>

class Client
{
	ENetAddress address;
	ENetHost *client;
	ENetEvent event;
	ENetPacket *packet;
	ENetPeer *peer;
	bool connected;

public:
	/*
	*
	* Initializes ENET and binds an atexit event.
	* Returns prints an error and waits for an input if the initialization fails.
	*
	*/
	Client();
	~Client();

	/*
	*
	* Set-up the client. The address_name parameter reffers to the IP address this client should connect to.
	*
	*/
	virtual void setupClient(const char *address_name);

	/*
	*
	* Send a packet to the server containing *data. The data will be a string. 
	* Only use this function if a Clienthandler is constructed and the server is set.
	*
	*/
	virtual void sendPacket(const char *data);
};

#endif