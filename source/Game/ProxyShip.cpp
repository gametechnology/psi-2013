#include "ProxyShip.h"

ProxyShip::ProxyShip(int teamID)
{
	this->_teamId = teamID;
}

ProxyShip::~ProxyShip()
{
	Entity::~Entity();
}

void ProxyShip::init()
{

}

void ProxyShip::onAdd()
{
	IrrlichtNode *model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	addChild(model);
}

void ProxyShip::update()
{

}
int ProxyShip::getTeamId()
{
	return this->_teamId;
}

void ProxyShip::HandleNetworkMessage(NetworkPacket packet)
{
	
}

