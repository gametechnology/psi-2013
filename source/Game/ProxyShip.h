#ifndef PROXYSHIP_H
#define PROXYSHIP_H

#include "Engine/Entity.h"
#include "NetworkInterface.h"
#include "Engine/IrrlichtNode.h"
#include "BasicMoverComponent.h"
#include "ShipInterface.h"
#include "Stations\Station.h"
#include "HealthComponent.h"

class ClientProxyShip :  public ShipInterface, public INetworkListener
{
public:
	ClientProxyShip(int teamId);
	~ClientProxyShip();

	int getTeamId();
	void HandleNetworkMessage(NetworkPacket packet);

	void init();
	void onAdd();
	void update();
	
private:
	int _teamId;
};

class ServerProxyShip : public ShipInterface, public INetworkListener
{

public:
	ServerProxyShip(int teamId);
	~ServerProxyShip();

	int getTeamId();
	void HandleNetworkMessage(NetworkPacket packet);

	bool StationInUse(StationType type);
	int getHealth();

	void init();
	void onAdd();
	void update();

private:

	void freeStation(StationType type);

	//returns false when the station is already in use
	bool enterStation(StationType type);

	int _teamId;
	std::map<StationType, bool> _stationsInUse;
	HealthComponent _healthComponent;
};
#endif