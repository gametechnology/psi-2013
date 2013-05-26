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

	virtual ENetHost* getServer();
	virtual ENetEvent* getEvent();

	/*
	*
	* Set-up the server.
	*
	*/
	virtual void setupServer(int host, int port);

	/*
	*
	* Run the server,
	*
	*/
	virtual void runServer();
};

#endif