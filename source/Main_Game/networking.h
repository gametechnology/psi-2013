#ifndef __NETWORKING_H_INCLUDED__
#define __NETWORKING_H_INCLUDED__

#include <enet\enet.h>
#include <string>

class ServerHandler
{
	ENetAddress address;
	ENetHost *server;
	ENetEvent event;
	ENetPacket *packet;

public:
	ServerHandler();

	~ServerHandler();

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
	ClientHandler();

	~ClientHandler();

	virtual void setupClient(const char *address_name);

	virtual void sendPacket(const char *data);
};

#endif