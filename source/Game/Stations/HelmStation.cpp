#include "HelmStation.h"
#include "../../Engine/Camera.h"
#include "../Thruster.h"

HelmStation :: HelmStation(Ship *ship) : Station( ship )
{
	this->_stationType = ST_HELM;
	this -> setStationDestroyed(false);
}

HelmStation :: ~HelmStation( )
{
}

void HelmStation :: DoCameraShake( )
{
	
}

void HelmStation :: update()
{
	Station :: update();

}

void HelmStation :: init()
{
	thrusters[0] = new Thruster(this->_ship, vector3df(0,0, -4), vector3df(0,0, -4), this->_ship->inertiaMatrix);
	thrusters[1] = new Thruster(this->_ship, vector3df(0,-2, 4), vector3df(0, 4, 0 ),this->_ship->inertiaMatrix);
	thrusters[2] = new Thruster(this->_ship, vector3df(0,2, -4), vector3df(0, 4, 0 ),this->_ship->inertiaMatrix);

	camera = new Camera(this, vector3df(0,0,0), vector3df(0,0,0));
	_ship->addComponent(camera);
}

