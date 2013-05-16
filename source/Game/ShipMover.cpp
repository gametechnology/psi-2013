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
void ShipMover::init() { }

void ShipMover::update() {
	//input logic
	
	//ShipMover::linearAcceleration = vector3df(0,0,0);
	//ShipMover::angularAcceleration = vector3df(0,0,0);
	
	//FORWARD/BACKWARD
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_R) && thrust < maxFwdSpeed)
		thrust += 0.1f;
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_F) && thrust > maxBwdSpeed)
		thrust -= 0.1f;
	
	//ROLL
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_Q))
		entity->transform->angularVelocity->X -= 1;
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_E))
		entity->transform->angularVelocity->X += 1;
	
	//YAW 
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_A))
		entity->transform->angularVelocity->Y -= 1;
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_D))
		entity->transform->angularVelocity->Y += 1;

	//PITCH
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_W))
		entity->transform->angularVelocity->Z -= 1;
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_S))
		entity->transform->angularVelocity->Z += 1;

	*entity->transform->angularVelocity *= 0.90f;
	thrust *= 0.95f;
	
	
	BasicMoverComponent::update();

	//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);
	//movementPacket << id; // ID van het ship
	movementPacket << entity->transform->position;
	movementPacket << entity->transform->rotation;
	movementPacket << entity->transform->velocity; 
	movementPacket << entity->transform->acceleration; 
	movementPacket << entity->transform->angularAccelaration; 
	movementPacket << entity->transform->angularVelocity;
	
	//Send packet to server
	if(Network::GetInstance()->IsServer()){
		if (lastsend + 1 < time(0) ){
			Network::GetInstance()->SendServerPacket(movementPacket, false);
			lastsend = time(0) ;
		}
	}
}
