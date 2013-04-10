#include "Engine\Network.h"

bool Network::isInitialized = false;
Network* Network::instance = 0;

Network::Network()
{
	isServer = false;
}

Network::~Network()
{
	isInitialized = false;
}

Network* Network::GetInstance()
{
	if(!isInitialized)
	{
		instance = new Network();
		isInitialized = true;
	}

	return instance;
}