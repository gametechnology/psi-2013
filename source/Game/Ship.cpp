#include "Ship.h"
#include "Stations/Station.h"
#include "ShipMover.h"
#include "SendAndReceivePackets.h"
#include "PlayerManager.h"
#include "GameScene.h"
#include "Shipmap.h"

vector3df startPosition;
vector3df startRotation;

ObjectPool<Laser>* Ship::laserPool;

Ship::Ship(vector3df position, vector3df rotation, int teamId) : ShipInterface ()
{
	this->transform->position = position;
	this->transform->rotation = rotation;
	this->_teamId = teamId;
	this->fillStationList();
	Network::GetInstance()->AddListener(PacketType::CLIENT_SHIP_MOVEMENT, this);
	Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_ENTER_STATION_ACCEPTED, this );
	Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_ENTER_STATION_DENIED, this );
	setInertiaMatrix(2,2,2,2);
	Network::GetInstance()->AddListener(CLIENT_REQUEST_ENTER_STATION, this);
	Network::GetInstance()->AddListener(CLIENT_LEAVE_STATION, this);
}

Ship::~Ship(void)
{
}

void Ship::onAdd() {
	ShipInterface::onAdd();
	startPosition = vector3df(0,0,-100);
	startRotation = vector3df(0,0,0);
	this->transform->position = startPosition;
	this->transform->rotation = startRotation;
//	Network::GetInstance()->AddListener(ClIENT_IN_LOBBY, this);
	IrrlichtNode *model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	model->transform->rotation.X += 180;
	addChild(model);

	this->env = game->device->getGUIEnvironment();
	this->_currentStation = NULL;

	addChild(_defenceStation		= new DefenceStation(this));
	addChild(_helmStation			= new HelmStation(this));
	addChild(_navigationStation		= new NavigationStation(this));
	addChild(_weaponStation			= new WeaponStation(this));
	addChild(_powerStation			= new PowerStation(this));

	this->init();


	this->_defenceStation->disable();
	this->_helmStation->disable();
	this->_navigationStation->disable();
	this->_weaponStation->disable();
	this->_powerStation->disable();
	
	this->shipHealthComponent = new ShipHealthComponent(this);
	addComponent(shipHealthComponent);
	//Thrusters
	_thrusters[0] = new Thruster(vector3df(0,0, -4), vector3df(0, 4, -4), this);
	_thrusters[1] = new Thruster(vector3df(0,-2, 4), vector3df(0, 4, 4 ), this);
	_thrusters[2] = new Thruster(vector3df(0,2, -4), vector3df(0, -4, -4 ), this);
	_thrusters[3] = new Thruster(vector3df(0,2, -4), vector3df(0, -4, 4 ), this);

	irr::core::stringw strShipHealth			= "ship health: "; 
	strShipHealth +	irr::core::stringw();

	irr::core::stringw strDefenceHealth			= "Defence Station health: "		+ this->_defenceStation->getHealth();
	irr::core::stringw strHelmHealth			= "Helm Station health: "			+ this->_helmStation->getHealth();
	irr::core::stringw strNavigationHealth		= "Navigation Station health: "		+ this->_navigationStation-> getHealth();
	irr::core::stringw strPowerHealth			= "Power Station health: "			+ this->_powerStation->getHealth();
	irr::core::stringw strWeaponHealth			= "Weapon Station health: "			+ this->_weaponStation->getHealth();
	this->shipHealth				= env->addStaticText(strShipHealth.c_str(),			rect<s32>(40,  80, 300, 100), false);	this->shipHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->defenceStationHealth		= env->addStaticText(strDefenceHealth.c_str(),		rect<s32>(40, 100, 300, 120), false);	this->defenceStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->helmStationHealth			= env->addStaticText(strHelmHealth.c_str(),			rect<s32>(40, 120, 300, 140), false);	this->helmStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->navigationStationHealth	= env->addStaticText(strNavigationHealth.c_str(),	rect<s32>(40, 140, 300, 160), false);	this->navigationStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->powerStationHealth		= env->addStaticText(strPowerHealth.c_str(),		rect<s32>(40, 160, 300, 180), false);	this->powerStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->weaponStationHealth		= env->addStaticText(strWeaponHealth.c_str(),		rect<s32>(40, 180, 300, 200), false);	this->weaponStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	
	irr::core::stringw strPing = "Ping :" + 0;
	this->pingGuiText = env->addStaticText(strPing.c_str(), rect<s32>(500,  30, 700, 50), false);	this->pingGuiText->setOverrideColor(video::SColor(255, 255, 255, 255));

	
	//Todo: Remove debug info from helptext!
	help = new HudHelpText(L"Move your player with 'WASD\nPress 'E' to enter a station", vector2df(100,100), vector2df(1280 - (2*100),720 - (2*100)));
	
	
	playerInfoScreen = new PlayerInfoScreen(vector2df(500,0), vector2df(1280 - 500, 720));
	
	addComponent(help);
	addComponent(playerInfoScreen);

	help->init();
	playerInfoScreen->init();
	//Todo: Reset the helptext to above text when you leave a station without entering another!
}

void Ship::fillStationList()
{
	this->_stationsInUse = std::map<StationType, bool>();
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_DEFENCE, false));
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_HELM, false));
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_NAVIGATION, false));
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_POWER, false));
	this->_stationsInUse.insert(std::pair<StationType, bool>(ST_WEAPON, false));
}

void Ship::init() 
{
	//Isn't called
	/*irr::core::stringw strShipHealth			= "ship health: "; 
	strShipHealth +	irr::core::stringw();

	irr::core::stringw strDefenceHealth			= "Defence Station health: "		+ this->_defenceStation->getHealth();
	irr::core::stringw strHelmHealth			= "Helm Station health: "			+ this->_helmStation->getHealth();
	irr::core::stringw strNavigationHealth		= "Navigation Station health: "	+ this->_navigationStation-> getHealth();
	irr::core::stringw strPowerHealth			= "Power Station health: "		+ this->_powerStation->getHealth();
	irr::core::stringw strWeaponHealth			= "Weapon Station health: "		+ this->_weaponStation->getHealth();
	this->shipHealth				= env->addStaticText(strShipHealth.c_str(),			rect<s32>(40,  80, 300, 100), false);	this->shipHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->defenceStationHealth		= env->addStaticText(strDefenceHealth.c_str(),		rect<s32>(40, 100, 300, 120), false);	this->defenceStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->helmStationHealth			= env->addStaticText(strHelmHealth.c_str(),			rect<s32>(40, 120, 300, 140), false);	this->helmStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->navigationStationHealth	= env->addStaticText(strNavigationHealth.c_str(),	rect<s32>(40, 140, 300, 160), false);	this->navigationStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->powerStationHealth		= env->addStaticText(strPowerHealth.c_str(),		rect<s32>(40, 160, 300, 180), false);	this->powerStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->weaponStationHealth		= env->addStaticText(strWeaponHealth.c_str(),		rect<s32>(40, 180, 300, 200), false);	this->weaponStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

	this->updateShipHealth();

	startPosition = vector3df(0,0,-100);
	startRotation = vector3df(0,0,0);
	this->transform->position = &startPosition;
	this->transform->rotation = &startRotation;*/
	
	ShipInterface::init();

}
	
int Ship::getTeamId()
{
	return this->_teamId;
}

Station *Ship :: GetStation( StationType s )
{
	switch( s )
	{
	case ST_DEFENCE:
		return this->_defenceStation;
		break;
	case ST_HELM:
		return this->_helmStation;
		break;
	case ST_NAVIGATION:
		return this->_navigationStation;
		break;
	case ST_POWER:
		return this->_powerStation;
		break;
	case ST_WEAPON:
		return this->_weaponStation;
		break;
	};
	return NULL;
}

bool Ship::StationInUse(StationType type)
{
	return this->_stationsInUse.find(type)->second;
}

void Ship::freeStation(StationType type)
{
	this->_stationsInUse.find(type)->second = false;
}

bool Ship::enterStation(StationType type)
{
	if(this->StationInUse(type))
		return false;

	this->_stationsInUse.find(type)->second = true;
	this->SwitchToStation(type);
	return true;
}

irr::core::stringw Ship::varToString(irr::core::stringw str1, float var){
	stringw str = L"";
	str += str1;
	str += (int)var;	
	return str;
}
irr::core::stringw Ship::varToString(irr::core::stringw str1, float var, irr::core::stringw str2){
	stringw str = L"";
	str += str1;
	str += (int)var;
	str += str2;
	return str;
}

void Ship :: update()
{
	ShipInterface :: update();

	PlayerManager ::GetInstance()->PingSend();
	PlayerManager ::GetInstance()->NoPingCounter();
	CheckChangeInput();

	
    stringw strPing = "Ping:" + PlayerManager::GetInstance()->getTimeTaken();
	this->pingGuiText->setText(		(varToString("Ping:", (float)PlayerManager::GetInstance()->getTimeTaken())).c_str());

	//updating the text for testing the health
	stringw strShipHealth		= "ship health: "				+ this->getShipHealth();
	stringw strDefenceHealth	= "Defence Station health: "	+ this->_defenceStation->getHealth();
	stringw strHelmHealth		= "Helm Station health: "		+ this->_helmStation->getHealth();
	stringw strNavigationHealth = "Navigation Station health: " + this->_navigationStation-> getHealth();
	stringw strPowerHealth		= "Power Station health: "		+ this->_powerStation->getHealth();
	stringw strWeaponHealth		= "Weapon Station health: "		+ this->_weaponStation->getHealth();

	this->shipHealth->setText(				(varToString("Ship HP : ",		(float)this->getShipHealth())					).c_str());
	this->defenceStationHealth->setText(	(varToString("Defence HP: ",	(float)this->_defenceStation->getHealth())		).c_str());
	this->helmStationHealth->setText(		(varToString("Helm HP: ",		(float)this->_helmStation->getHealth())		).c_str());
	this->navigationStationHealth->setText(	(varToString("Navigation HP: ",	(float)this->_navigationStation->getHealth())	).c_str());
	this->powerStationHealth->setText(		(varToString("Power HP: ",		(float)this->_powerStation->getHealth())		).c_str());
	this->weaponStationHealth->setText(		(varToString("Weapon HP: ",		(float)this->_weaponStation->getHealth())		).c_str());

	//If the ship has no more health and is not already destroyed, destroy it
	if(this->getShipHealth() <= 0 && this->_shipDestroyed == false) {
		this->_shipDestroyed = true;
	}	

	if(game->input->isKeyboardButtonPressed(KEY_MINUS)){
		a = rand() % 50;
		shipHealthComponent->assignDamage(a);
	}
}

Thruster** Ship :: GetThrusters()
{
	return this->_thrusters;
}
matrix4* Ship::GetInertiaMatrix(){
	return this->_inertiaMatrix;
}

void Ship :: CheckChangeInput()
{
	StationType st = StationType :: ST_NONE;
	if (game->input->isKeyboardButtonPressed(KEY_KEY_1))
		st = ST_DEFENCE;
	
		//SwitchToStation(ST_DEFENCE);

	if (game->input->isKeyboardButtonPressed(KEY_KEY_2))
		st = ST_HELM;
		//SwitchToStation(ST_HELM);

	if (game->input->isKeyboardButtonPressed(KEY_KEY_3))
		st = ST_WEAPON;
		//SwitchToStation(ST_WEAPON);

	if (game->input->isKeyboardButtonPressed(KEY_KEY_4))
		st = ST_NAVIGATION;
		//SwitchToStation(ST_NAVIGATION);

	if (game->input->isKeyboardButtonPressed(KEY_KEY_5))
		st = ST_POWER;
		//SwitchToStation(ST_POWER);
	if ( st == StationType :: ST_NONE ) return;

	if(!Network::GetInstance()->IsServer())
	{
		NetworkPacket packet = NetworkPacket( PacketType :: CLIENT_REQUEST_ENTER_STATION );
		packet << PlayerManager :: GetInstance( ) -> GetLocalPlayerData( ) -> id << PlayerManager::GetInstance()->GetLocalPlayerData()->team_id << ( int )st;
		Network :: GetInstance( ) -> SendPacket( packet, true );
		//TODO: check that this works for the server as well as for the clients.
	}else
	{
		if(this->enterStation(st))
		{
			NetworkPacket acceptPacket = NetworkPacket(SERVER_ENTER_STATION_ACCEPTED);
			acceptPacket << PlayerManager::GetInstance()->GetLocalPlayerData()->id << PlayerManager::GetInstance()->GetLocalPlayerData()->team_id << st;
			Network::GetInstance()->SendServerPacket(acceptPacket, true);
		}else
		{
			//notify server player that the station is in use
		}
	}
}

//Swith to a specific station
void Ship :: SwitchToStation(StationType stationType)
{
	//Check if we are already on this station
	if (this->_currentStation != NULL)
	{
		if (this->_currentStation->GetStationType() == stationType)
			return;

		//First remove the currentStation from the shipComponents
		if(this->_currentStation->enabled)
			this->_currentStation->disable();
	}

	//Find the new station
	this->_currentStation = this->GetStation(stationType);

	//Init and add the new station
	this->_currentStation->enable();
	PlayerManager :: GetInstance( ) -> StationUpdated( stationType );
}

void Ship :: draw()
{
	ShipInterface :: draw();
}

int Ship :: getShipHealth()
{
	/*return (this->_defenceStation->getHealth() +
		this->_helmStation->getHealth() +
		this->_navigationStation->getHealth() +
		this->_powerStation->getHealth() +
		this->_weaponStation->getHealth());*/
	return shipHealthComponent->health;
}

bool Ship :: getShipDestroyed()
{
	return this->_shipDestroyed;
}


void Ship::setInertiaMatrix(float h, float w, float d, float m)
{
	//used for the momentum of inertia, currently not used, only m is used (mass')
	_inertiaMatrix = new matrix4();
	float inertiaData[16];
	for(unsigned i = 0; i < 16; i++)
	{
		inertiaData[i] = 0.0f;
	}

	inertiaData[0] = (((1.0f / 5.0f) * m) * (pow(w, 2) + pow(d, 2)));
	inertiaData[5] = (((1.0f / 5.0f) * m) * (pow(h, 2) + pow(d, 2)));
	inertiaData[10] = (((1.0f / 5.0f) * m) * (pow(h, 2) + pow(w, 2)));
	inertiaData[15] = 1.0f;

	_inertiaMatrix->setM(inertiaData);
}

void Ship::fireLaser()
{
	Laser* laser = this->laserPool->GetFreeObject();
	if(laser != NULL)
	{
		laser->fire(this->transform, this->scene->getIrrlichtSceneManager()->getActiveCamera()->getTarget(), 10 * _weaponStation->getPower()/100, 1.0);
		std::cout << "weapon fired" << std::endl;

		if(!Network::GetInstance()->IsServer()) {
			NetworkPacket firepacket = NetworkPacket(PacketType::CLIENT_FIRE_LASER);
			firepacket << *laser;
			Network::GetInstance()->SendPacket(firepacket, true);
		}
	}
}

void Ship::addIShipListener(IShipListener* listener) {
	listeners.push_back(listener);
}

void Ship::removeIShipListener(IShipListener* listener){
	listeners.pop_back();
}


void Ship::notifyIShipListeners(ShipMessage message){
	if(message == LEAVESTATION)
		

	for(std::list<IShipListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
		(*it)->handleShipMessage(message);
	}
}

void Ship::leaveStation(StationType station)
{
	NetworkPacket packet(PacketType::CLIENT_LEAVE_STATION);
	packet << PlayerManager::GetInstance()->GetLocalPlayerData()->team_id << station << PlayerManager :: GetInstance( ) -> GetLocalPlayerData( ) -> id;
	Network::GetInstance()->SendPacketToAllClients(packet, true);

	if ( Network :: GetInstance( ) -> IsServer( ) )
	{
		PlayerManager :: GetInstance( ) -> OnClientLeaveStationReceived( PlayerManager :: GetInstance( ) -> GetLocalPlayerData( ) -> id );
	}

	this->freeStation(station);
	this->_currentStation->disable();
	this->_currentStation = NULL;
	((GameScene*)this->scene)->getShipMap()->enable();
	
	//this->notifyIShipListeners(LEAVESTATION);
}


void Ship::HandleNetworkMessage(NetworkPacket packet)
{
	int player_id;
	int team_id;
	int st;
	if ( packet.GetType( ) == PacketType :: CLIENT_SHIP_MOVEMENT )
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

				//Apply updates 
				if(_currentStation != NULL && _currentStation->GetStationType() == ST_WEAPON){
					((WeaponStation*)_currentStation)->rotationForeign = rotation;
				}
				else{
					//Read the information from the network packet
					transform->rotation = rotation;

				}
			}
	}	
	else if ( packet.GetType( ) == PacketType :: SERVER_ENTER_STATION_ACCEPTED )
	{
		printf("packet received\n");
		packet >> player_id >> team_id >> st;
		if ( player_id == PlayerManager :: GetInstance( ) -> GetLocalPlayerData( ) -> id )
		{
			SwitchToStation( ( StationType )st );
			((GameScene*)this->scene)->getShipMap()->disable();
		}else if(team_id == PlayerManager::GetInstance()->GetLocalPlayerData()->team_id)
		{
			printf("station bezet\n");
			this->_stationsInUse.find((StationType)st)->second = true;
		}
	} else if( packet.GetType( ) == PacketType :: SERVER_ENTER_STATION_DENIED )
	{
		packet >> player_id;
		if ( player_id == PlayerManager :: GetInstance( ) -> GetLocalPlayerData( ) -> id )
		{
			//TODO: Show the player that he SHALL NO PASS!!!!
		}		
	}else if(packet.GetType() == CLIENT_REQUEST_ENTER_STATION && Network::GetInstance()->IsServer())
	{
		packet >> player_id >> team_id >> st;
		if(team_id == PlayerManager::GetInstance()->GetLocalPlayerData()->team_id)
		{
			if(StationInUse((StationType)st))
			{
				NetworkPacket declinePacket = NetworkPacket(SERVER_ENTER_STATION_DENIED);
				declinePacket << player_id;
				Network::GetInstance()->SendServerPacket(declinePacket, true);
				return;
			}
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
}

void Ship::foundEnemyBase() {
	
	_foundEnemyBase = true;
	printf("Found Enemy Base!!!! :)");

}

void Ship::backAtOwnBase() {

	if (_foundEnemyBase == true){
		_backAtOwnBase = true;
		printf("You won!!"); 
	}

	else
		printf("Find the enemy base first!");
	
}