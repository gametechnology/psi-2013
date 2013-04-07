#include "Ship.h"
#include <Windows.h>

Ship::Ship(Composite * parent, vector3df position, vector3df rotation) : Entity(parent)
{
	setInertiaMatrix(50, 35, 100, 500);
	Ship::position = position;
	Ship::orientation = rotation;
	up = vector3df(0,1,0);
	forward = vector3df(0,0,1);
	right = vector3df(1,0,0);
	Ship::input = &eventReceiver;
}


Ship::~Ship(void)
{
}

void Ship::init(int station){

	stationnumber = station;
	nrOfBullets = 10;
	ammo = new Bullet[nrOfBullets];
	bulletNr = 0;
	shootingInterval = 0;

	for (int i = 0; i < nrOfBullets; i++)
	{
		Game::getCurrentScene()->addComponent(&ammo[i]);
	}

	Entity::init();
	camera = new Camera(this, vector3df(0,0,0), vector3df(0,0,0));
	addComponent(camera);
	
	if(station == 0)
	{
		currentstation = new HelmStation(this);
		addComponent(currentstation);
		network = new Net(false, camera, ammo);
		
	}
	else 
	{
		currentstation = new WeaponStation(this);
		addComponent(currentstation);
		network = new Net(true, ammo, ((WeaponStation*)currentstation)->cameramover);
	}

	
	thrusters[0] = new Thruster(this, vector3df(0,0, -4), vector3df(0,0, -4), &inertiaMatrix);
	thrusters[1] = new Thruster(this, vector3df(0,-2, -4), vector3df(0, -4, 0 ),&inertiaMatrix);
	thrusters[2] = new Thruster(this, vector3df(0,2, -4), vector3df(0, 4, 0 ),&inertiaMatrix);

	ShipMover* shipMover = new ShipMover(this, thrusters);
	this->addComponent(shipMover);
}

void Ship::handleMessage(unsigned int message, void* data){

}

void Ship::setInertiaMatrix(float h, float w, float d, float m){

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

	matrix4 inertiaMatrix;
	inertiaMatrix.setM(inertiaData);
}