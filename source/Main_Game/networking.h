#ifndef __NETWORKING_H_INCLUDED__
#define __NETWORKING_H_INCLUDED__

#include <enet\enet.h>
#include <string>

class ServerHandler
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
	ServerHandler();

	/*
	*
	* Destroys all the variables held by this class.
	*
	*/
	~ServerHandler();

	/*
	*
	* Set-up the server. This is not yet implemented.
	*
	*/
	virtual void setupServer();
};

class ClientHandler 
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
	ClientHandler();

	/*
	*
	* Destroys all the variables held by this class.
	*
	*/
	~ClientHandler();

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