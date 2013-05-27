#ifndef SHIP_MOVER
#define SHIP_MOVER

#include <Engine/Core.h>
#include <Engine/Component.h>
#include <Irrlicht/irrlicht.h>

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
	Ship* _ship;
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
	irr::core::matrix4* inertiaMatrix_;
	irr::core::vector3df shipRotation_;
	irr::core::vector3df worldLinForce_;
	irr::core::vector3df worldAngForce_;
	irr::core::vector3df rotation_;
	irr::core::vector3df localLinForce_;
	irr::core::vector3df localAngForce_;
	irr::core::matrix4 rotationMatrix;
	irr::core::vector3df* shipLinAcc_;
	irr::core::vector3df* shipAngAcc_;
	irr::core::vector3df LocalToWorld(irr::core::vector3df* localVector, irr::core::matrix4* rMatrix);

	void NotMovementStuff();
	CalculateRotation mathRotation;
	

	float maxFwdSpeed;
	float maxBwdSpeed;

};

#endif