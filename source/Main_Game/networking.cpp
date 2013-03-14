#include "networking.h"
#include <iostream>

ServerHandler::ServerHandler()
{
	printf("Creating ServerHandler.\n");
	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		getchar();
	}
	atexit(enet_deinitialize);
}

ServerHandler::~ServerHandler()
{
}

void ServerHandler::setupServer()
{
}

ClientHandler::ClientHandler()
{
	printf("Creating ClientHandler.\n");
	connected = false;
	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		getchar();
	}
	atexit(enet_deinitialize);
}

ClientHandler::~ClientHandler()
{
}

void ClientHandler::setupClient()
{
}