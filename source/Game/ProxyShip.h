#ifndef PROXYSHIP_H
#define PROXYSHIP_H

#include "Engine/Entity.h"
#include "NetworkInterface.h"
#include "Engine/IrrlichtNode.h"
#include "BasicMoverComponent.h"
#include "ShipInterface.h"
#include "Stations\Station.h"
#include "HealthComponent.h"
#include "Irrlicht\irrlicht.h"

class ClientProxyShip :  public ShipInterface, public INetworkListener
{
public:
	ClientProxyShip(vector3df position, vector3df rotation, int teamId);
	~ClientProxyShip();

	int getTeamId();
	void HandleNetworkMessage(NetworkPacket packet);

	virtual void init();
	virtual void onAdd();
	virtual void update();
	
private:
	int _teamId;
	IrrlichtNode* _model;
};

class ServerProxyShip : public ShipInterface, public INetworkListener
{

public:
	ServerProxyShip(vector3df position, vector3df rotation, int teamId);
	~ServerProxyShip();

	int getTeamId();
	void HandleNetworkMessage(NetworkPacket packet);

	bool StationInUse(StationType type);
	int getHealth();

	virtual void init();
	virtual void onAdd();
	virtual void update();

private:

	void freeStation(StationType type);

	//returns false when the station is already in use
	bool enterStation(StationType type);

	int _teamId;
	std::map<StationType, bool> _stationsInUse;
	HealthComponent _healthComponent;
	IrrlichtNode* _model;
};
#endif