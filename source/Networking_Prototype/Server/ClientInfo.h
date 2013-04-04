#include <string>
#include <enet/enet.h>


class ClientInfo
{
public:
	ClientInfo();
	ClientInfo(UINT32 hostAddress, UINT16 port, ENetPeer* peer);
	~ClientInfo();

	UINT32 hostAddress;
	UINT16 port;
	ENetPeer* peer;
};

