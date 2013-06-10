#include "ProxyShip.h"


////////////////////////////////////////////
//Client proxyship below
///////////////////////////////////////////

ClientProxyShip::ClientProxyShip(vector3df position, vector3df rotation, int teamID) : ShipInterface()
{
	this->_teamId = teamID;
	*this->transform->position = position;
	*this->transform->rotation = rotation;
	Network::GetInstance()->AddListener(CLIENT_SHIP_MOVEMENT, this);
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
	_model->transform->rotation->X += 180;
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
	if(packet.GetType() == PacketType::CLIENT_SHIP_MOVEMENT)
	{
		//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
		int id;
		irr::core::vector3df position;
		irr::core::vector3df rotation;
		irr::core::vector3df velocity;
		irr::core::vector3df acceleration;
		irr::core::vector3df angularAcceleration;
		irr::core::vector3df angularVelocity;

		packet >> id >> position >> rotation >> velocity >> acceleration >> angularAcceleration >> angularVelocity;

		if(id == this->_teamId)
		{
			*transform->acceleration = acceleration;
			*transform->angularAccelaration = angularAcceleration;
			*transform->angularVelocity = angularVelocity;
			*transform->position = position;
			*transform->velocity = velocity;
			*transform->rotation = rotation;
		}
	}
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
	Network::GetInstance()->AddListener(CLIENT_SHIP_MOVEMENT, this);
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
	if(packet.GetType() == PacketType::CLIENT_SHIP_MOVEMENT)
	{
		//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
		int id;
		irr::core::vector3df position;
		irr::core::vector3df rotation;
		irr::core::vector3df velocity;
		irr::core::vector3df acceleration;
		irr::core::vector3df angularAcceleration;
		irr::core::vector3df angularVelocity;

		packet >> id >> position >> rotation >> velocity >> acceleration >> angularAcceleration >> angularVelocity;

		if(id == this->_teamId)
		{
			*transform->acceleration = acceleration;
			*transform->angularAccelaration = angularAcceleration;
			*transform->angularVelocity = angularVelocity;
			*transform->position = position;
			*transform->velocity = velocity;
			*transform->rotation = rotation;
		}
	}
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
	_model->transform->rotation->X += 180;
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


