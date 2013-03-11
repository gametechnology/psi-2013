#include "Thruster.h"

//enum for the rotation of the ship 
	typedef enum
	{
		Left = 1,
		Right = 2,
		Up = 3,
		Down = 4,
		RollLeft = 5,
		RollRight = 6

	} ThrusterPointingSide;

Thruster::Thruster(vector3df position, vector3df centerShipPosition, Thruster::ThrusterPointingSide thrusterSide, float maxThrust)
{
	Thruster::maxThrust = maxThrust;
	Thruster::position = position;
	Thruster::distanceFromCenter = position - centerShipPosition;
	Thruster::thrusterSide = thrusterSide;
	Thruster::direction = Thruster::setForce();
}

vector3df Thruster::UseThruster(float energy)
{
	vector3df distanceFromCenter = Thruster::distanceFromCenter;
	vector3df torque = distanceFromCenter.crossProduct(Thruster::direction);
	torque = torque.normalize();
	torque *= 0.05f;
	return torque;
}

void Thruster::setPosition(vector3df centerShipPosition)
{
	Thruster::position = centerShipPosition + Thruster::distanceFromCenter;
}

vector3df Thruster::setForce()
{
	vector3df direction = vector3df(0,0,0);

	switch(Thruster::thrusterSide)
	{
	case Left:
		direction = vector3df(1,0,0);
		break;

	case Right:
		direction = vector3df(-1,0,0);
		break;

	case Up:
		direction = vector3df(0,1,0);
		break;

	case Down:
		direction = vector3df(0,-1,0);
		break;

	case RollLeft:
		direction = vector3df(0,0,1);
		break;

	case RollRight:
		direction = vector3df(0,0,-1);
		break;
	}

	return direction;
}