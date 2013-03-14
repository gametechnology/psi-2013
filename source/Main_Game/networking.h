#ifndef __NETWORKING_H_INCLUDED__
#define __NETWORKING_H_INCLUDED__

#include <enet\enet.h>

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

	virtual void setupClient();
};

#endif