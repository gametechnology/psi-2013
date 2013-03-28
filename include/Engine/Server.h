#ifndef SERVER
#define SERVER

#include <enet\enet.h>
#include <string>

class Server
{
	// The host adress.
	ENetAddress address;

	// Pointer to the server.
	ENetHost *server;
	
	// Event from which received data will be read.
	ENetEvent event;

	// The packet to send as answer.
	ENetPacket *packet;

public:
	/*
	*
	* Initializes ENET and binds an atexit event.
	* Returns prints an error and waits for an input if the initialization fails.
	*
	*/
	Server();
	~Server();

	/*
	*
	* Set-up the server. This is not yet implemented.
	*
	*/
	virtual void setupServer();
};

#endif