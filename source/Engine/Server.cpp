#include "Engine\Server.h"
#include <iostream>
#include <enet/enet.h>

Server::Server()
{
	printf("Creating Server.\n");
	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		getchar();
	}
	atexit(enet_deinitialize);
}

Server::~Server()
{
	delete &address;
	delete &server;
	delete &event;
	delete &packet;
	enet_host_destroy(server);
}

void Server::setupServer()
{
}