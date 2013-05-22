#include "ShipMover.h"
#include "Engine\Entity.h"
#include "Ship.h"
#include "BasicMoverComponent.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// To test the ship's movement the powerstation needs to be commented in ship.cpp and in station.cpp!! ///////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShipMover::ShipMover(Ship* _ship) : BasicMoverComponent() {
	this->_ship = _ship;
	
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
	//set the current rotation matrix which will be used to transform the local acceleration into world acceleration
	this->shipRotation_= *(entity->transform->rotation);
	//rotationMatrix.setRotationDegrees(shipRotation_);
	
	//handle input.
	//when a button is pressed, the linear and angular of the used thrusters will be added up	d'alemberts principle
	
	if(input->isKeyboardButtonDown(irr::KEY_KEY_W)){
		std::cout << "[ShipMover] W IS PRESSED";
		//localAngForce_ += thrusters_[3]->angularForce;			<----- THIS PART BREAKS STUFF
		//localAngForce_ += thrusters_[4]->angularForce;
		//localLinForce_ += thrusters_[3]->linearForce;
		//localLinForce_ += thrusters_[4]->linearForce;
	}

	/*because of the thruster implentation, these forces will assume the ship has no rotation. Hence local forces.
	the local forces will be transformed into world forces by getting the ships rotation, make a rotationMatrix out of it
	and rotate the accumulated force.*/
	worldLinForce_ = this->LocalToWorld(&localLinForce_, &rotationMatrix);		//i think it breaks here, with the fucntion and rotation
	worldAngForce_ = this->LocalToWorld(&localAngForce_, &rotationMatrix);

	*shipLinAcc_ += worldLinForce_; //force should be divided by mass. but the ship has no mass, I think.
	*shipAngAcc_ += worldAngForce_;

	/*this method is used because it uses the least amount of complicated calculations I could think of.
	the complicated math is only done once in the thruster, and only simple adding and matrix transformations
	are done each frame.*/
	


	//seriously guys. Why did you use my shipmover component for something that isn't even moving the ship?
	//shipmover moves the ship. That's all functionality it has and needs. Or put it in something similar like BasicMoverComponent,
	//only name it NetMovementComponent!
	//hey, that would make a hell lotta sense
	//just think about it.
	//you can use the same component for every moving object that needs to be updated over the network
	//like enemies, asstroids, missiles
	//I am such a genius. I expect full credits of this amazing idea.
}
void ShipMover::ResetForces(){
	localAngForce_ = vector3df(0,0,0);
	localLinForce_ = vector3df(0,0,0);
	worldAngForce_ = vector3df(0,0,0);
	worldLinForce_ = vector3df(0,0,0);
}
vector3df ShipMover::LocalToWorld(vector3df* local, matrix4* rMatrix){
	vector3df temp = vector3df(0,0,0);
	//rMatrix->transformVect(temp, *local);
	return temp;
}
void ShipMover::NotMovementStuff(){
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
	if(Network::GetInstance()->IsServer())
		Network::GetInstance()->SendServerPacket(movementPacket, false);

}
