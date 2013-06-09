#include "ProxyShip.h"


////////////////////////////////////////////
//Client proxyship below
///////////////////////////////////////////

ClientProxyShip::ClientProxyShip(vector3df position, vector3df rotation, int teamID) : ShipInterface()
{
	this->_teamId = teamID;
	*this->transform->position = position;
	*this->transform->rotation = rotation;
}

ClientProxyShip::~ClientProxyShip()
{
	Entity::~Entity();
}

void ClientProxyShip::init()
{
	ShipInterface::init();
}

void ClientProxyShip::onAdd()
{
	this->enable();
	_model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	addChild(_model);

	this->init();

	ShipInterface::onAdd();
}

void ClientProxyShip::update()
{
	ShipInterface::update();
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


ServerProxyShip::ServerProxyShip(vector3df position, vector3df rotation, int teamId) : ShipInterface()
{
	this->_teamId = teamId;
	this->_stationsInUse = std::map<StationType, bool>();
	*this->transform->position = position;
	*this->transform->rotation = rotation;
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
	ShipInterface::init();
}

void ServerProxyShip::onAdd()
{
	this->enable();
	this->_model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	this->addChild(_model);

	this->init();

	ShipInterface::onAdd();
}

void ServerProxyShip::update()
{
	ShipInterface::update();
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


