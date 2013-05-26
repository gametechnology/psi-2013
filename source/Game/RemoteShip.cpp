#include "RemoteShip.h"
#include "ShipMover.h"
#include "NetworkMover.h"

vector3df _startPosition;
vector3df _startRotation;

RemoteShip::RemoteShip(vector3df position, vector3df rotation) : Entity ()
{
	this->transform->position = &position;
	this->transform->rotation = &rotation;

}

RemoteShip::~RemoteShip(void)
{
	Entity::~Entity();
}

void RemoteShip::onAdd() {
	Entity::onAdd();
		
//	Network::GetInstance()->AddListener(ClIENT_IN_LOBBY, this);
	IrrlichtNode *model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	addChild(model);
	
	//Thrusters
	_thrusters[0] = new Thruster(vector3df(0,0, -4), vector3df(0, 4, -4));
	_thrusters[1] = new Thruster(vector3df(0,-2, 4), vector3df(0, 4, 4 ));
	_thrusters[2] = new Thruster(vector3df(0,2, -4), vector3df(0, -4, -4 ));
	_thrusters[3] = new Thruster(vector3df(0,2, -4), vector3df(0, -4, 4 ));

	irr::core::stringw strShipHealth			= "ship health: "; 
	strShipHealth +	irr::core::stringw();

	//_startPosition = vector3df(0,0,-100);
	//_startRotation = vector3df(0,0,0);
	//this->transform->position = &_startPosition;
	//this->transform->rotation = &_startRotation;

	addComponent(new NetworkMover());

	_laserCount = 10;

	for (int i = 0; i < _laserCount; i++)
		_laser.push_back(new Laser());

	for (int i = 0; i < _laserCount; i++)
		scene->addChild(_laser[i]);

	_laserCounter = 0;
}

void RemoteShip::init() 
{
	Entity::init();

}

irr::core::stringw RemoteShip::varToString(irr::core::stringw str1, float var){
	stringw str = L"";
	str += str1;
	str += (int)var;	
	return str;
}
irr::core::stringw RemoteShip::varToString(irr::core::stringw str1, float var, irr::core::stringw str2){
	stringw str = L"";
	str += str1;
	str += (int)var;
	str += str2;
	return str;
}

void RemoteShip :: update()
{
	Entity :: update();

	//If the ship has no more health and is not already destroyed, destroy it
	//if(this->getShipHealth() <= 0 && this->_shipDestroyed == false) {
	//	this->_shipDestroyed = true;
	//}
}

Thruster** RemoteShip :: GetThrusters()
{
	return this->_thrusters;
}

void RemoteShip :: draw()
{
	Entity :: draw();
}

bool RemoteShip :: getShipDestroyed()
{
	return this->_shipDestroyed;
}

void RemoteShip::setInertiaMatrix(float h, float w, float d, float m)
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

void RemoteShip::fireLaser()
{
	//_laser[_laserCounter++]->fire(this, this->scene->getIrrlichtSceneManager()->getActiveCamera()->getTarget(), 1.0);
	//
	//if(_laserCounter >= _laserCount)
	//	_laserCounter = 0;
}