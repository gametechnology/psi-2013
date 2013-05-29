#include "ShipMover.h"

using namespace irr;
using namespace irr::core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// To test the ship's movement the powerstation needs to be commented in ship.cpp and in station.cpp!! ///////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShipMover::ShipMover(Core* core, Ship* ship) : BasicMoverComponent(ship) {
	_ship = ship;
	_core = core;

	lastsend = time(0);
	maxFwdSpeed = 10.f;
	maxBwdSpeed = -10.f;
}

ShipMover::~ShipMover() 
{
}

void ShipMover::draw() 
{
}

void ShipMover::onAdd(){
	thrusters_ = _ship->GetThrusters();
	shipAngAcc_ = _ship->getAngularAcceleration();
	shipLinAcc_ = _ship->getAcceleration();
}

void ShipMover::init() { }

void ShipMover::update() {
	this->shipRotation_= *(_parent->getRotation());

	if(_core->getInput()->isKeyboardButtonDown(irr::KEY_KEY_W)){
		std::cout << "[ShipMover] W IS PRESSED";	
	}

	worldLinForce_ = this->LocalToWorld(&localLinForce_, &rotationMatrix);
	worldAngForce_ = this->LocalToWorld(&localAngForce_, &rotationMatrix);

	*shipLinAcc_ += worldLinForce_;
	*shipAngAcc_ += worldAngForce_;
}
void ShipMover::ResetForces(){
	localAngForce_ = vector3df(0,0,0);
	localLinForce_ = vector3df(0,0,0);
	worldAngForce_ = vector3df(0,0,0);
	worldLinForce_ = vector3df(0,0,0);
}

vector3df ShipMover::LocalToWorld(vector3df* local, matrix4* rMatrix)
{
	vector3df temp = vector3df(0,0,0);
	return temp;
}
void ShipMover::NotMovementStuff(){
	BasicMoverComponent::update();

	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);

	movementPacket << _parent->getPosition();
	movementPacket << _parent->getRotation();
	movementPacket << _parent->getVelocity(); 
	movementPacket << _parent->getAcceleration(); 
	movementPacket << _parent->getAngularAcceleration(); 
	movementPacket << _parent->getAngularVelocity();
	
	if (lastsend + 1 < time(0) ){
		Network::GetInstance()->SendPacketToAllClients(movementPacket, false);
		lastsend = time(0) ;
	}

}

