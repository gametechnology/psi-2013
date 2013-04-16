#include "Ship.h"
#include "Stations/Station.h"

Ship::Ship( Composite * parent ) : Entity ( parent )
{
	this->env = Game :: device->getGUIEnvironment();
	
	this->setInertiaMatrix(50, 35, 100, 500);
	this->position =  vector3df(0,0,0);
	this->orientation = vector3df(0,0,0);

	//TODO remove temp stuff
	this->_defenceStation		= new DefenceStation( this );
	this->_helmStation			= new HelmStation( this );
	this->_navigationStation	= new NavigationStation( this );
	this->_weaponStation		= new WeaponStation( this );
	//this->_powerStation		= new PowerStation( this );

	this->_defenceStation		-> Initialize();
	this->_helmStation		-> Initialize();
	this->_navigationStation	-> Initialize();
	this->_weaponStation		-> Initialize();
	//this->_powerStation		-> Initialize();

	addComponent(_defenceStation);
	addComponent(_helmStation);
	addComponent(_navigationStation);
	addComponent(_weaponStation);
	//addComponent(_powerStation);

	this->updateShipHealth();
	this->_shipDestroyed = false;

	stringw strShipHealth = "ship health: " + this->getShipHealth();
	stringw strDefenceHealth = "Defence Station health: " + this->_defenceStation->getHealth();
	stringw strHelmHealth = "Helm Station health: " + this->_helmStation->getHealth();
	stringw strNavigationHealth = "Navigation Station health: " + this->_navigationStation-> getHealth();
	//stringw strPowerHealth = "Power Station health: " + this->_powerStation->getHealth();
	stringw strWeaponHealth = "Weapon Station health: " + this->_weaponStation->getHealth();

	this->shipHealth				= env->addStaticText(strShipHealth.c_str(),			rect<s32>(40,  80, 200, 100), false);
	this->defenceStationHealth	= env->addStaticText(strDefenceHealth.c_str(),		rect<s32>(40, 100, 200, 120), false);
	this->helmStationHealth		= env->addStaticText(strHelmHealth.c_str(),			rect<s32>(40, 120, 200, 140), false);
	this->navigationStationHealth = env->addStaticText(strNavigationHealth.c_str(),	rect<s32>(40, 140, 200, 160), false);
	//this->powerStationHealth		= env->addStaticText(strPowerHealth.c_str(),		rect<s32>(40, 160, 200, 180), false);
	this->weaponStationHealth		= env->addStaticText(strWeaponHealth.c_str(),		rect<s32>(40, 180, 200, 200), false);
}

Ship::~Ship(void)
{
	this->removeComponent(_defenceStation);
	this->removeComponent(_helmStation);
	this->removeComponent(_navigationStation);
	this->removeComponent(_weaponStation);
	//this->removeComponent(_powerStation);
}

Station *Ship :: GetStation( StationType s )
{
	switch( s )
	{
	case ST_DEFENCE:
		return this->_defenceStation;
		break;
	case ST_HELM:
		return this->_helmStation;
		break;
	case ST_NAVIGATION:
		return this->_navigationStation;
		break;
	case ST_POWER:
		return this->_powerStation;
		break;
	case ST_WEAPON:
		return this->_weaponStation;
		break;
	};
	return NULL;
}

void Ship :: update()
{
	Entity :: update();
	this->updateShipHealth();

	//updating the text for testing the health
	stringw strShipHealth = "ship health: " + this->getShipHealth();
	stringw strDefenceHealth = "Defence Station health: " + this->_defenceStation->getHealth();
	stringw strHelmHealth = "Helm Station health: " + this->_helmStation->getHealth();
	stringw strNavigationHealth = "Navigation Station health: " + this->_navigationStation-> getHealth();
	//stringw strPowerHealth = "Power Station health: " + this->_powerStation->getHealth();
	stringw strWeaponHealth = "Weapon Station health: " + this->_weaponStation->getHealth();

	this->shipHealth->setText(				(varToString("Ship HP : ",				this->getShipHealth())					).c_str());
	this->defenceStationHealth->setText(	(varToString("Defence Station HP: ",	this->_defenceStation->getHealth())		).c_str());
	this->helmStationHealth->setText(		(varToString("Helm Station HP: ",		this->_helmStation->getHealth())		).c_str());
	this->navigationStationHealth->setText(	(varToString("Navigation Station HP: ",	this->_navigationStation->getHealth())	).c_str());
	//this->powerStationHealth->setText(		(varToString("Power Station HP: ",		this->_powerStation->getHealth())		).c_str());
	this->weaponStationHealth->setText(		(varToString("Weapon Station HP: ",		this->_weaponStation->getHealth())		).c_str());

	if(this->_shipHealth <= 0 && this->_shipDestroyed == false) {
		this->_shipDestroyed == true;
	}

	if(this->_helmStation->getHealth() <= 0 && this->_helmStation->getStationDestroyed() == false) {
		this->_helmStation->setStationDestroyed(true);
	}

	if(this->_defenceStation->getHealth() <= 0 && this->_defenceStation->getStationDestroyed() == false) {
		this->_defenceStation->setStationDestroyed(true);
	}

	if(this->_navigationStation->getHealth() <= 0 && this->_navigationStation->getStationDestroyed() == false) {
		this->_navigationStation->setStationDestroyed(true);
	}

	/*if(this->_powerStation->getHealth() <= 0 && this->_powerStation->getStationDestroyed() == false) {
		this->_powerStation->setStationDestroyed(true);
	}*/

	if(this->_weaponStation->getHealth() <= 0 && this->_weaponStation->getStationDestroyed() == false) {
		this->_weaponStation->setStationDestroyed(true);
	}
}

void Ship :: updateShipHealth()
{
	this->_shipHealth = 
		this->_defenceStation->getHealth() +
		this->_helmStation->getHealth() +
		this->_navigationStation->getHealth() +
		//this->_powerStation->getHealth() +
		this->_weaponStation->getHealth();
}

void Ship :: draw()
{
	Entity :: draw();
}

int Ship :: getShipHealth()
{
	return this->_shipHealth;
}

bool Ship :: getShipDestroyed()
{
	return this->_shipDestroyed;
}

void Ship::init()
{
	Entity::init();
}

void Ship::handleMessage(unsigned int message, void* data){

}

void Ship::setInertiaMatrix(float h, float w, float d, float m){

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

	matrix4 inertiaMatrix;
	inertiaMatrix.setM(inertiaData);
}

stringw Ship::varToString(stringw str1, float var){
	stringw str = L"";
	str += str1;
	str += (int)var;	
	return str;
}
stringw Ship::varToString(stringw str1, float var, stringw str2){
	stringw str = L"";
	str += str1;
	str += (int)var;
	str += str2;
	return str;
}