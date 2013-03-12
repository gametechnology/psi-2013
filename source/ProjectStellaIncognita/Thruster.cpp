#include "Thruster.h"

//enum for the rotation of the ship 
typedef enum
{
	Left = 1,
	Right = 2,
	Up = 3,
	Down = 4,
	RollLeft = 5,
	RollRight = 6,
	Forward = 7,
	Backward = 8

} ThrusterPointingSide;

float Thruster::smallThrusterForce;	
float Thruster::bigThrusterForce;

Thruster::Thruster(vector3df position, vector3df centerShipPosition, Thruster::ThrusterPointingSide thrusterSide)
{
	Thruster::position = position;
	Thruster::distanceFromCenter = position - centerShipPosition;
	Thruster::thrusterSide = thrusterSide;
	Thruster::direction = Thruster::setForce();
}

vector3df Thruster::UseThruster()
{
	vector3df distanceFromCenter = Thruster::distanceFromCenter;
	vector3df torque = distanceFromCenter.crossProduct(Thruster::direction);
	torque = torque.normalize();
	torque *= smallThrusterForce;

	return torque;
}

float Thruster::UseThruster(float mass)
{
	float force;
	switch(Thruster::thrusterSide)
	{
	case Forward:
		force = bigThrusterForce;
		break;
	default:
		force = smallThrusterForce;
		break;
	}
	float acceleration = (1.0f / mass) * force;

	return acceleration;
}

void Thruster::setPosition(vector3df centerShipPosition)
{
	Thruster::position = centerShipPosition + Thruster::distanceFromCenter;
}

void Thruster::setEnergy(float energy)
{
	Thruster::energy = energy;
}

float Thruster::getEnergy()
{
	float energy = Thruster::energy;
	return energy;
}

vector3df Thruster::setForce()
{
	vector3df direction = vector3df(0,0,0);

	switch(Thruster::thrusterSide)
	{
	case Left:
		direction = vector3df(0,1,0);
		break;

	case Right:
		direction = vector3df(0,-1,0);
		break;

	case Up:
		direction = vector3df(-1,0,0);
		break;

	case Down:
		direction = vector3df(1,0,0);
		break;

	case RollLeft:
		direction = vector3df(1,1,0);
		break;

	case RollRight:
		direction = vector3df(1,1,0);
		break;
	}

	return direction;
}