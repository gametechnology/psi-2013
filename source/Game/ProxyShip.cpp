#include "ProxyShip.h"
#include "PlayerManager.h"


////////////////////////////////////////////
//Client proxyship below
///////////////////////////////////////////

ClientProxyShip::ClientProxyShip(vector3df position, vector3df rotation, int teamID) : ShipInterface()
{
	this->_teamId = teamID;
	this->transform->position = position;
	this->transform->rotation = rotation;
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
	_model->transform->rotation.X += 180;
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
			transform->acceleration = acceleration;
			transform->angularAccelaration = angularAcceleration;
			transform->angularVelocity = angularVelocity;
			transform->position = position;
			transform->velocity = velocity;
			transform->rotation = rotation;
		}
	}
}


///////////////////////////////////////////////////////
//Server proxyship below
///////////////////////////////////////////////////////


ServerProxyShip::ServerProxyShip(vector3df position, vector3df rotation, int teamId) : ShipInterface()
{
	this->_teamId = teamId;
	this->transform->position = position;
	this->transform->rotation = rotation;
	this->_stationsHealth = std::map<StationType, int>();
	//Add all the healths from stations together
	for (int i = 0; i < 5; i++)
	{
		_stationsHealth.insert(std::pair<StationType, int>((StationType)i, 100));
	}
	this->fillStationList();
	Network::GetInstance()->AddListener(CLIENT_SHIP_MOVEMENT, this);
	Network::GetInstance()->AddListener(CLIENT_REQUEST_ENTER_STATION, this);
	Network::GetInstance()->AddListener(CLIENT_HEALTH_CHANGED, this);
	Network::GetInstance()->AddListener(CLIENT_LEAVE_STATION, this);
}

ServerProxyShip::~ServerProxyShip()
{

}

void ServerProxyShip::fillStationList()
{
	this->_stationsInUse = std::map<StationType, bool>();
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_DEFENCE, false));
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_HELM, false));
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_NAVIGATION, false));
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_POWER, false));
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_WEAPON, false));
}

int ServerProxyShip::getTeamId()
{
	return this->_teamId;
}

void ServerProxyShip::HandleNetworkMessage(NetworkPacket packet)
{
	int player_id;
	int team_id;
	int st;
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
			transform->acceleration = acceleration;
			transform->angularAccelaration = angularAcceleration;
			transform->angularVelocity = angularVelocity;
			transform->position = position;
			transform->velocity = velocity;
			transform->rotation = rotation;
		}
	}else if(packet.GetType() == CLIENT_REQUEST_ENTER_STATION && Network::GetInstance()->IsServer())
	{
		packet >> player_id >> team_id >> st;
		if(team_id != PlayerManager::GetInstance()->GetLocalPlayerData()->team_id)
		{
			printf("received packet\n");
			if(StationInUse((StationType)st))
			{
				NetworkPacket declinePacket = NetworkPacket(SERVER_ENTER_STATION_DENIED);
				declinePacket << player_id;
				Network::GetInstance()->SendServerPacket(declinePacket, true);
				return;
			}
			printf("accepted\n");
			this->_stationsInUse.find((StationType)st)->second = true;
			NetworkPacket acceptPacket = NetworkPacket(SERVER_ENTER_STATION_ACCEPTED);
			acceptPacket << player_id << team_id << st;
			Network::GetInstance()->SendServerPacket(acceptPacket, true);
		}

	}else if(packet.GetType() == CLIENT_LEAVE_STATION)
	{
		packet >> team_id >> st;
		if(this->_teamId == team_id)
		{
			freeStation((StationType)st);
		}
	}
	if(packet.GetType() == PacketType::CLIENT_HEALTH_CHANGED)
	{
		//Station and health
		int id;
		int stationType;
		int health;
		
		packet >> id;
		packet >> stationType;
		packet >> health;

		//Check if we are the same team
		if(id == this->getTeamId())
		{
			//set the health for this stationtype
			this->SetStationHealth((StationType)stationType,health);
		}
	}
}

void ServerProxyShip::SetStationHealth(StationType stationType, int health)
{
	this->_stationsHealth.find(stationType)->second = health;
}

int ServerProxyShip::GetStationHealth(StationType stationType)
{
	return this->_stationsHealth.find(stationType)->second;
}

bool ServerProxyShip::StationInUse(StationType type)
{
	return this->_stationsInUse.find(type)->second;
}

int ServerProxyShip::getHealth()
{
	int totalHealth = 0;

	//Add all the healths from stations together
	for (int i = 0; i < _stationsHealth.size(); i++)
	{
		totalHealth += GetStationHealth((StationType)i);
	}
	cout<<totalHealth<<endl;
	return totalHealth;

}

void ServerProxyShip::init()
{
	ShipInterface::init();
}

void ServerProxyShip::onAdd()
{
	this->enable();
	this->_model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	_model->transform->rotation.X += 180;
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


