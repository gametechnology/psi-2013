#include "Ship.h"
#include <Windows.h>

Ship::Ship(Composite * parent, vector3df position, vector3df rotation) : Entity(parent)
{
	Ship::drag = 0.99f;
	Ship::position = position;
	Ship::orientation = rotation;

	Ship::input = &eventReceiver;
}


Ship::~Ship(void)
{
}

void Ship::init(int station){

	Entity::init();
	camera = new Camera(this, vector3df(0,0,0), vector3df(0,0,0));
	addComponent(camera);
	
	if(station == 0)
	{
		currentstation = new HelmStation(this);
		addComponent(currentstation);
		network = Net(false, camera);
		
	}
	else 
	{
		currentstation = new WeaponStation(this);
		addComponent(currentstation);
		network = Net(true, ((WeaponStation*)currentstation)->cameramover);
	}

	
	thrusters[0] = new Thruster(this, vector3df(0,0, -4), vector3df(0,0, -4));
	thrusters[1] = new Thruster(this, vector3df(0,0, -4), vector3df(-4, 0, 0 ));
	thrusters[2] = new Thruster(this, vector3df(0,0, -4), vector3df(4, 0, 0 ));

	ShipMover* shipMover = new ShipMover(this, thrusters);
	this->addComponent(shipMover);
}

void Ship::update(){
	
	Entity::update();
	//OutputDebugString(L"update");
	
	if(input->IsKeyDown(KEY_DOWN)){
		OutputDebugString(L"DOWN IS PRESSED\n");
	}
	
}

void Ship::handleMessage(unsigned int message, void* data){

}
