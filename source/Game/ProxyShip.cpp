#include "ProxyShip.h"


////////////////////////////////////////////
//Client proxyship below
///////////////////////////////////////////

ClientProxyShip::ClientProxyShip(int teamID)
{
	this->_teamId = teamID;
}

ClientProxyShip::~ClientProxyShip()
{
	Entity::~Entity();
}

void ClientProxyShip::init()
{
	Entity::init();
}

void ClientProxyShip::onAdd()
{
	IrrlichtNode *model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	addChild(model);

	Entity::onAdd();
}

void ClientProxyShip::update()
{

}
int ClientProxyShip::getTeamId()
{
	return this->_teamId;
}

void ClientProxyShip::HandleNetworkMessage(NetworkPacket packet)
{
	
}


///////////////////////////////////////////////////////
//Server proxyship below
///////////////////////////////////////////////////////


ServerProxyShip::ServerProxyShip(int teamId)
{
	this->_teamId = teamId;
	this->_stationsInUse = std::map<StationType, bool>();
}

ServerProxyShip::~ServerProxyShip()
{

}

int ServerProxyShip::getTeamId()
{
	return this->_teamId;
}

void ServerProxyShip::HandleNetworkMessage(NetworkPacket packet)
{

}

bool ServerProxyShip::StationInUse(StationType type)
{
	return this->_stationsInUse.find(type)->second;
}

int ServerProxyShip::getHealth()
{
	return this->_healthComponent.health;
}

void ServerProxyShip::init()
{
	Entity::init();
}

void ServerProxyShip::onAdd()
{
	IrrlichtNode *model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	addChild(model);

	Entity::onAdd();
}

void ServerProxyShip::update()
{
	Entity::update();
}

void ServerProxyShip::freeStation(StationType type)
{
	this->_stationsInUse.find(type)->second = false;
}

bool ServerProxyShip::enterStation(StationType type)
{
	if(this->StationInUse(type))
		return false;

	this->_stationsInUse.find(type)->second = true;
	return true;
}


