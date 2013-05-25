#pragma once
#include "Engine\Game.h"
#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"
#include "Thruster.h"
#include "CalculateRotation.h"
#include "Ship.h"
#include "BasicMoverComponent.h"
class ShipMover : public BasicMoverComponent
{
public:
	ShipMover(Ship* ship);
	~ShipMover(void);
	void Activate();
	Ship		*_ship;
	int lastsend;
	virtual void init();
	virtual void onAdd();
	virtual void update();
	virtual void draw();
	virtual void handleMessage(unsigned int message, void* data = 0){};

private:
	void ResetForces();
	InputManager* input;
	Thruster** thrusters_;
	matrix4* inertiaMatrix_;
	vector3df shipRotation_;
	vector3df worldLinForce_;
	vector3df worldAngForce_;
	vector3df rotation_;
	vector3df localLinForce_;
	vector3df localAngForce_;
	matrix4 rotationMatrix;
	vector3df* shipLinAcc_;
	vector3df* shipAngAcc_;
	vector3df LocalToWorld(vector3df* localVector, matrix4* rMatrix);

	void NotMovementStuff();
	CalculateRotation mathRotation;
	

	float maxFwdSpeed;
	float maxBwdSpeed;

};

