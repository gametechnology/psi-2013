#ifndef PROXYSHIP_H
#define PROXYSHIP_H

#include "Engine/Entity.h"
#include "NetworkInterface.h"
#include "Engine/IrrlichtNode.h"
#include "BasicMoverComponent.h"
#include "ShipInterFace.h"

class ProxyShip :  public ShipInterFace, public INetworkListener
{
public:
	ProxyShip(int teamId);
	~ProxyShip();

	int getTeamId();
	void HandleNetworkMessage(NetworkPacket packet);

	void init();
	void onAdd();
	void update();
	
private:
	int _teamId;
};
#endif