#include "../Server/ClientInfo.h"

ClientInfo::ClientInfo()
{
}

ClientInfo::ClientInfo(UINT32 hostAddress, UINT16 port, ENetPeer* peer)
{
	this->hostAddress = hostAddress;
	this->port = port;
	this->peer = peer;
}


ClientInfo::~ClientInfo(void)
{
}
