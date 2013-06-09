#ifndef SERVERPROXYSHIP_H
#define SERVERPROXYSHIP_H

#include "Engine/Entity.h"
#include "NetworkInterface.h"
#include "Engine/IrrlichtNode.h"
#include "BasicMoverComponent.h"
#include "ShipInterFace.h"

class ServerProxyShip :  public ShipInterFace, public INetworkListener
{
public:
	ServerProxyShip(int teamId);
	~ServerProxyShip();

	int getTeamId();
	void HandleNetworkMessage(NetworkPacket packet);

	void init();
	void onAdd();
	void update();
	
private:
	int _teamId;
};
#endif