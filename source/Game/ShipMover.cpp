#include "ShipMover.h"
#include "Engine\Entity.h"
#include "Ship.h"
#include "BasicMoverComponent.h"


ShipMover::ShipMover(Ship* _ship) : BasicMoverComponent() {
	this->_ship = _ship;
}

ShipMover::~ShipMover() { }
void ShipMover::draw() { }
void ShipMover::init() { }

void ShipMover::update() {
	//input logic
	
	ShipMover::linearAcceleration = vector3df(0,0,0);
	ShipMover::angularAcceleration = vector3df(0,0,0);
	
	if(getGame()->input->isKeyboardButtonPressed(KEY_KEY_W))
	{
		this->linearAcceleration += _ship->GetThrusters()[0]->transform->force;
		this->angularAcceleration += *(_ship->GetThrusters()[0]->transform->angularAccelaration) * 0.0001;
	}
	if(getGame()->input->isKeyboardButtonPressed(KEY_KEY_A))
	{
		this->linearAcceleration += _ship->GetThrusters()[1]->transform->force;
		this->angularAcceleration += *(_ship->GetThrusters()[1]->transform->angularAccelaration) * 0.0001;
	}
	if(getGame()->input->isKeyboardButtonPressed(KEY_KEY_D))
	{
		this->linearAcceleration += _ship->GetThrusters()[2]->transform->force;
		this->angularAcceleration += *(_ship->GetThrusters()[2]->transform->angularAccelaration) * 0.0001;
	}
	
	//Roll 
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

	//printf("rotation: x:%f, y:%f, z:%f\n", entityParent->orientation.X, entityParent->orientation.Y, entityParent->orientation.Z);

	*entity->transform->angularVelocity *= 0.90f;
	
	
	BasicMoverComponent::update();

	//Vec3 position, Vec3 orientation, Vec3 acceleration, Vec3 angularAcceleration
	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);
	vector3df yey = vector3df(entity->transform->position->X, entity->transform->position->Y, entity->transform->position->Z);
	movementPacket << yey;
	//movementPacket << vector3df(entityParent->orientation.X, entityParent->orientation.Y, entityParent->orientation.Z);
	//movementPacket << vector3df(entityParent->accelaration.X, entityParent->accelaration.Y, entityParent->accelaration.Z);
	//movementPacket << vector3df(entityParent->angularAccelaration.X, entityParent->angularAccelaration.Y, entityParent->angularAccelaration.Z);

	//Send packet to server
	Network::GetInstance()->SendPacket(movementPacket, false);
}
