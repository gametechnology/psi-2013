#include "Thruster.h"
#include "Engine\Component.h"
#include "Engine\Game.h"
#include "Engine\Entity.h"

Thruster::Thruster(Composite* parent, vector3df position, vector3df initialDirection, matrix4* inertiaMatrix) : Entity(parent)
{
	Thruster::position = position;
	Thruster::direction = initialDirection;
	//Normalize the vectors so I can use them to calculate the dot product and the cross product.
	nPosition = position.normalize();
	nDirection = direction.normalize();

	//torque is the cross product of the direction and position to the objects centre.
	//		t = p x f
	//torque is the axis the force will rotate the object around.
	f32 dot = nPosition.dotProduct(nDirection);
	if(dot != -1){
		Thruster::torque = nPosition.crossProduct(nDirection);
	} else{
		torque = vector3df(0,0,0);
	}

	//the angular acceleration direction this thruster provides is calculated
	// Ö = I -1 * t
	if(dot != -1){
		inertiaMatrix->transformVect(angularAccelaration, torque);
	} else{
		angularAccelaration = vector3df(0,0,0);
	}
	printAng();

	//TODO: divide the force into vectors to get the linear component and magnitude of angular component pass 
	//the linear component to linearAcceleration. Use the angular component's length for the angular acceleration
	//to give the angular acceleration it's lenght. 
	//impediments:	The camera works with euler angles right now, so it'll bug. It'll have to be rewritten with
	//quaternions.
}

void Thruster::printAng(){
	std::cout << "angular acceleration: [" << angularAccelaration.X << "," << angularAccelaration.Y << "," << angularAccelaration.Z << "]\n";
	std::cout << "torque: [" << torque.X << "," << torque.Y << "," << torque.Z << "]\n";
	std::cout << "dir: [" << direction.X << "," << direction.Y << "," << direction.Z << "]\n";
}

Thruster::~Thruster()
{


}

void Thruster::Activate(){

}
void Thruster::update(){
	

}
void Thruster::init(){

}

void Thruster::draw(){

}

void Thruster::handleMessage(unsigned int message, void* data)
{

}
