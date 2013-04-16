#include "HelmStation.h"
#include "Engine/Camera.h"
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

	//input logic
	vector3df linearAcceleration = vector3df(0,0,0);
	vector3df angularAccelaration = vector3df(0,0,0);
	
	if(Game::input->isKeyboardButtonDown(KEY_KEY_W))
	{
		//thrusters[0]->printAng();
		linearAcceleration += thrusters[0]->linearForce;
		angularAccelaration += (thrusters[0]->angularAccelaration * 0.0001);
	}
	if(Game::input->isKeyboardButtonDown(KEY_KEY_A))
	{
		//thrusters[1]->printAng();
		linearAcceleration += thrusters[1]->linearForce;
		angularAccelaration += (thrusters[1]->angularAccelaration * 0.0001);
	}
	if(Game::input->isKeyboardButtonDown(KEY_KEY_D))
	{
		//thrusters[2]->printAng();
		linearAcceleration += thrusters[2]->linearForce;
		angularAccelaration += (thrusters[2]->angularAccelaration * 0.0001);
	}
	
	this->_ship->linearAcceleration = linearAcceleration;
	this->_ship->angularAccelaration = angularAccelaration;
}

void HelmStation :: init()
{
	thrusters[0] = new Thruster(this->_ship, vector3df(0,0, -4), vector3df(0,0, -4), &this->_ship->inertiaMatrix);
	thrusters[1] = new Thruster(this->_ship, vector3df(0,-2, 4), vector3df(0, 4, 0 ),&this->_ship->inertiaMatrix);
	thrusters[2] = new Thruster(this->_ship, vector3df(0,2, -4), vector3df(0, 4, 0 ),&this->_ship->inertiaMatrix);

	camera = new Camera(this->_ship, vector3df(0,0,0), vector3df(0,0,0));
	_ship->addComponent(camera);
}

