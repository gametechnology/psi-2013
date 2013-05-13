#include "DummyShip.h"
#include "ShipMover.h"


DummyShip::DummyShip(vector3df position) : Entity ()
{
	this->transform->position = &position;
}

DummyShip::~DummyShip(void)
{
	
}

void DummyShip::onAdd() {
	IrrlichtNode *model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	addChild(model);
}

void DummyShip::init() 
{
	startPosition = vector3df(0,0,-100);
	startRotation = vector3df(0,0,0);
	this->transform->position = &startPosition;
	this->transform->rotation = &startRotation;

	Entity::init();
}


irr::core::stringw DummyShip::varToString(irr::core::stringw str1, float var){
	stringw str = L"";
	str += str1;
	str += (int)var;	
	return str;
}
irr::core::stringw DummyShip::varToString(irr::core::stringw str1, float var, irr::core::stringw str2){
	stringw str = L"";
	str += str1;
	str += (int)var;
	str += str2;
	return str;
}

void DummyShip :: update()
{
	Entity :: update();
}

//Swith to a specific station

void DummyShip :: draw()
{
	Entity :: draw();
}

void DummyShip::setInertiaMatrix(float h, float w, float d, float m)
{
	//used for the momentum of inertia, currently not used, only m is used (mass)
	float inertiaData[16];
	for(unsigned i = 0; i < 16; i++)
	{
		inertiaData[i] = 0.0f;
	}

	inertiaData[0] = (((1.0f / 5.0f) * m) * (pow(w, 2) + pow(d, 2)));
	inertiaData[5] = (((1.0f / 5.0f) * m) * (pow(h, 2) + pow(d, 2)));
	inertiaData[10] = (((1.0f / 5.0f) * m) * (pow(h, 2) + pow(w, 2)));
	inertiaData[15] = 1.0f;

	_inertiaMatrix->setM(inertiaData);
}
