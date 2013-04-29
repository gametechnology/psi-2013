#include "Thruster.h"
#include "Engine\Component.h"
#include "Engine\Game.h"
#include "Engine\Entity.h"
#include <iostream>

Thruster::Thruster(Entity *parent, irr::core::vector3df position, irr::core::vector3df initialDirection) : Entity(*parent)
{
	this->transform->position = &position;
	this->transform->rotation = &initialDirection;
	//Normalize the vectors so I can use them to calculate the dot product and the cross product.
	nPosition = position.normalize();
	nDirection = direction.normalize();

	//torque is the cross product of the direction and position to the objects centre.
	//		t = p x f
	//torque is the axis the force will rotate the object around.
	f32 dot = nPosition.dotProduct(nDirection);
	if(dot != -1){
		this->torque = nPosition.crossProduct(nDirection);
	} else{
		this->torque = irr::core::vector3df(0,0,0);
	}

	
	//printAng();

	//TODO: divide the force into vectors to get the linear component and magnitude of angular component pass 
	//the linear component to linearAcceleration. Use the angular component's length for the angular acceleration
	//to give the angular acceleration it's lenght. 
	//impediments:	The camera works with euler angles right now, so it'll bug. It'll have to be rewritten with
	//quaternions. http://www.educreations.com/course/lesson/view/sim3d-les-1-opgave-9/5466461/
	//here's a link of Gerke de Boer explaining vector to vector projections
	//
	float labda = (direction.dotProduct(position)) / (position.dotProduct(position)) ;
	forceComponent1 = position*labda;
	forceComponent2  = direction - forceComponent1;
	//not sure which component is which. either one could be linear, still needs testing, but build is down :(


	linearForce = forceComponent1;
	
	//the angular acceleration direction this thruster provides is calculated
	// Ö = I -1 * t
	if(dot != -1){			//this is an earlyish escape to prevent unnecesarry matrix manipulato
		//inertiaMatrix->transformVect(angularForce, torque);
		angularForce*= forceComponent2.getLength();
	} else{
		angularForce = irr::core::vector3df(0,0,0);
	}
}

void Thruster::printAng(){
	std::cout << "angular acceleration: [" << angularForce.X << "," << angularForce.Y << "," << angularForce.Z << "]\n";
	std::cout << "torque: [" << torque.X << "," << torque.Y << "," << torque.Z << "]\n";
	std::cout << "dir: [" << direction.X << "," << direction.Y << "," << direction.Z << "]\n";
}

Thruster::~Thruster() { }
void Thruster::Activate() { }
void Thruster::update() { }
void Thruster::init() { }
void Thruster::draw() { }
void Thruster::handleMessage(unsigned int message, void* data) { }
