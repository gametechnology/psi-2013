#include "Ship.h"
#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"

using namespace irr;
using namespace irr::core;

vector3df startPosition;
vector3df startRotation;

ObjectPool<Laser>* Ship::laserPool;

Ship::Ship(Core* core, Interface* ui, vector3df position, vector3df rotation) : GameObject()
{
	_core = core;
	_interface = ui;
	_position = &position;
	_rotation = &rotation;
	Network::GetInstance()->AddListener(CLIENT_SHIP_MOVEMENT, this);
}

Ship::~Ship()
{
	GameObject::~GameObject();
}

void Ship::init() 
{	
	startPosition = vector3df(0,0,-100);
	startRotation = vector3df(0,0,0);
	_position = &startPosition;
	_rotation = &startRotation;


	MeshComponent* _mesh = new MeshComponent(_core->getSmgr());
	addComponent(_mesh);
	_mesh->createMeshNode("../assets/Models/myship.obj");

	env = _core->getGuiEnv();
	_currentStation = NULL;

	_defenceStation = new DefenceStation(_core, _interface, this);
	_helmStation = new HelmStation(_core, _interface, this);
	_navigationStation = new NavigationStation(_core, _interface, this);
	_weaponStation	= new WeaponStation(_core, _interface, this);
	_powerStation = new PowerStation(_core, _interface, this);

	addComponent(_defenceStation);
	addComponent(_helmStation);
	addComponent(_navigationStation);
	addComponent(_weaponStation);
	addComponent(_powerStation);

	_defenceStation->init();
	_helmStation->init();
	_navigationStation->init();
	_weaponStation->init();
	_powerStation->init();

	_defenceStation->disable();
	_helmStation->disable();
	_navigationStation->disable();
	_weaponStation->disable();
	_powerStation->disable();


	//Thrusters
	_thrusters[0] = new Thruster(vector3df(0,0, -4), vector3df(0, 4, -4));
	_thrusters[1] = new Thruster(vector3df(0,-2, 4), vector3df(0, 4, 4 ));
	_thrusters[2] = new Thruster(vector3df(0,2, -4), vector3df(0, -4, -4 ));
	_thrusters[3] = new Thruster(vector3df(0,2, -4), vector3df(0, -4, 4 ));

	irr::core::stringw strShipHealth			= "ship health: "; 
	strShipHealth +	irr::core::stringw();

	irr::core::stringw strDefenceHealth			= "Defence Station health: "		+ _defenceStation->getHealth();
	irr::core::stringw strHelmHealth			= "Helm Station health: "			+ _helmStation->getHealth();
	irr::core::stringw strNavigationHealth		= "Navigation Station health: "		+ _navigationStation-> getHealth();
	irr::core::stringw strPowerHealth			= "Power Station health: "			+ _powerStation->getHealth();
	irr::core::stringw strWeaponHealth			= "Weapon Station health: "			+ _weaponStation->getHealth();

	//Todo: Remove debug info from helptext!
	help = new HudHelpText(_core, _interface, "Move your player with 'WASD\nPress 'E' to enter a station\nDEBUG!! Shortcuts to enter a station: '1', '2', '3', '4', '5'\nShortcuts can be used from inside every station", vector2df(100,100), vector2df(1280 - (2*100),720 - (2*100)));
	addComponent(help);

	shipHealth = env->addStaticText(strShipHealth.c_str(), rect<s32>(40,  80, 300, 100), false);	
	shipHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

	defenceStationHealth = env->addStaticText(strDefenceHealth.c_str(),	rect<s32>(40, 100, 300, 120), false);	
	defenceStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

	helmStationHealth = env->addStaticText(strHelmHealth.c_str(), rect<s32>(40, 120, 300, 140), false);	
	helmStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

	navigationStationHealth = env->addStaticText(strNavigationHealth.c_str(), rect<s32>(40, 140, 300, 160), false);	
	navigationStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

	powerStationHealth = env->addStaticText(strPowerHealth.c_str(), rect<s32>(40, 160, 300, 180), false);	
	powerStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

	weaponStationHealth = env->addStaticText(strWeaponHealth.c_str(), rect<s32>(40, 180, 300, 200), false);	
	weaponStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

	//Todo: Reset the helptext to above text when you leave a station without entering another!
	GameObject::init();
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
	GameObject::update();
	CheckChangeInput();

	//updating the text for testing the health
	stringw strShipHealth = "ship health: " + getShipHealth();
	stringw strDefenceHealth = "Defence Station health: " + _defenceStation->getHealth();
	stringw strHelmHealth = "Helm Station health: " + _helmStation->getHealth();
	stringw strNavigationHealth = "Navigation Station health: " + _navigationStation->getHealth();
	stringw strPowerHealth = "Power Station health: " + _powerStation->getHealth();
	stringw strWeaponHealth = "Weapon Station health: "	+ _weaponStation->getHealth();

	shipHealth->setText((varToString("Ship HP : ", (float)getShipHealth())).c_str());
	defenceStationHealth->setText((varToString("Defence HP: ", (float)_defenceStation->getHealth())).c_str());
	helmStationHealth->setText((varToString("Helm HP: ", (float)_helmStation->getHealth())).c_str());
	navigationStationHealth->setText((varToString("Navigation HP: ", (float)_navigationStation->getHealth())).c_str());
	powerStationHealth->setText((varToString("Power HP: ", (float)_powerStation->getHealth())).c_str());
	weaponStationHealth->setText((varToString("Weapon HP: ", (float)_weaponStation->getHealth())).c_str());

	//If the ship has no more health and is not already destroyed, destroy it
	if(this->getShipHealth() <= 0 && this->_shipDestroyed == false) {
		this->_shipDestroyed = true;
	}
}

void Ship::draw()
{
	GameObject::draw();
}

Thruster** Ship :: GetThrusters()
{
	return this->_thrusters;
}

void Ship :: CheckChangeInput()
{
	/*if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_1))
		SwitchToStation(ST_DEFENCE);

	if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_2))
		SwitchToStation(ST_HELM);

	if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_3))
		SwitchToStation(ST_WEAPON);

	if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_4))
		SwitchToStation(ST_NAVIGATION);

	if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_5))
		SwitchToStation(ST_POWER);*/
}

//Swith to a specific station
void Ship :: SwitchToStation(StationType stationType, Player* player)
{
	if (_currentStation != NULL)
	{
		if (_currentStation->GetStationType() == stationType)
			return;
		_currentStation->disable();
	}

	_currentStation = GetStation(stationType);
	_currentStation->setPlayerOccupation(player);
	_currentStation->enable();
}

int Ship :: getShipHealth()
{
	return(_defenceStation->getHealth() +
		_helmStation->getHealth() +
		_navigationStation->getHealth() +
		_powerStation->getHealth() +
		_weaponStation->getHealth());
}

bool Ship :: getShipDestroyed()
{
	return this->_shipDestroyed;
}

void Ship::setInertiaMatrix(float h, float w, float d, float m)
{
	//used for the momentum of inertia, currently not used, only m is used (mass)
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
		laser->fire(_position, _rotation, _core->getSmgr()->getActiveCamera()->getTarget(), 1.0);
		std::cout << "weapon fired" << std::endl;

		if(!Network::GetInstance()->IsServer()){
			NetworkPacket firepacket = NetworkPacket(CLIENT_FIRE_LASER);
			firepacket << *laser;
			Network::GetInstance()->SendPacket(firepacket, true);

		}
	}
}

void Ship::handleNetworkMessage(NetworkPacket packet)
{

	if(packet.GetType() == CLIENT_SHIP_MOVEMENT)
	{
		//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
		irr::core::vector3df position;
		irr::core::vector3df rotation;
		irr::core::vector3df velocity;
		irr::core::vector3df acceleration;
		irr::core::vector3df angularAcceleration;
		irr::core::vector3df angularVelocity;
		packet >> position;
		packet >> rotation;
		packet >> velocity;
		packet >> acceleration;
		packet >> angularAcceleration;
		packet >> angularVelocity;
		*_acceleration = acceleration;
		*_angularAcceleration = angularAcceleration;
		*_angularVelocity = angularVelocity;
		*_position = position;
		*_velocity = velocity;

		//Apply updates 
		if(_currentStation != NULL && _currentStation->GetStationType() == ST_WEAPON){
			((WeaponStation*)_currentStation)->rotationForeign = rotation;
		}
		else{
			//Read the information from the network packet
			*_rotation = rotation;
		}
	}
}