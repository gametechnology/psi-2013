#ifndef THRUSTER_H
#define THRUSTER_H

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Thruster
{
public:

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

	//constructor which sets the position and max thrust
	Thruster(vector3df position, vector3df centerShipPosition, ThrusterPointingSide thrusterSide, float maxThrust);

	//when called the thruster is used and returns the torque vector
	vector3df UseThruster(float energy);

	void setPosition(vector3df centerShipPosition);

private:
	vector3df position;
	vector3df distanceFromCenter;
	vector3df direction;
	float maxThrust;
	
	vector3df setForce();
	//the side which the ship will turn to when active
	ThrusterPointingSide thrusterSide;
};
#endif