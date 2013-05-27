#include "ShipMover.h"
#include "Engine\Entity.h"
#include "Ship.h"
#include "BasicMoverComponent.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// To test the ship's movement the powerstation needs to be commented in ship.cpp and in station.cpp!! ///////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShipMover::ShipMover(Ship* _ship) : BasicMoverComponent() {
	this->_ship = _ship;
	lastsend = time(0);
	maxFwdSpeed = 10.f;
	maxBwdSpeed = -10.f;
}

ShipMover::~ShipMover() { }
void ShipMover::draw() { }
void ShipMover::onAdd(){
	input = getGame()->input;
	thrusters_ = _ship->GetThrusters();
	shipAngAcc_ = _ship->transform->angularAccelaration;
	shipLinAcc_ = _ship->transform->acceleration;
}

void ShipMover::init() { }

void ShipMover::update() {
	this->shipRotation_= *(entity->transform->rotation);

	if(input->isKeyboardButtonDown(irr::KEY_KEY_W)){
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

	movementPacket << entity->transform->position;
	movementPacket << entity->transform->rotation;
	movementPacket << entity->transform->velocity; 
	movementPacket << entity->transform->acceleration; 
	movementPacket << entity->transform->angularAccelaration; 
	movementPacket << entity->transform->angularVelocity;
	
	if (lastsend + 1 < time(0) ){
		Network::GetInstance()->SendPacketToAllClients(movementPacket, false);
		lastsend = time(0) ;
	}

}

