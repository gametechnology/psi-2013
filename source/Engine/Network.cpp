#include "Engine\Network.h"
#include "Engine\NetworkPacket.h"

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

void Network::InitializeClient()
{
}

void Network::InitializeServer()
{
}

void Network::SendPacket(NetworkPacket packet, bool reliable)
{

}

void Network::AddListener(INetworkListener* listener)
{
	_listeners.push_back(listener);
}