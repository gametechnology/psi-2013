#include "Ship.h"
#include "Stations/Station.h"

Ship::Ship( Composite * parent ) : Entity ( parent )
{
	this -> env = Game :: device -> getGUIEnvironment();

	//TODO remove temp stuff
	this -> _defenceStation		= new DefenceStation( this );
	this -> _helmStation		= new HelmStation( this );
	this -> _navigationStation	= new NavigationStation( this );
	this -> _weaponStation		= new WeaponStation( this );
	this -> _powerStation		= new PowerStation( this );

	this -> _defenceStation		-> Initialize();
	this -> _helmStation		-> Initialize();
	this -> _navigationStation	-> Initialize();
	this -> _weaponStation		-> Initialize();
	this -> _powerStation		-> Initialize();

	addComponent(_defenceStation);
	addComponent(_helmStation);
	addComponent(_navigationStation);
	addComponent(_weaponStation);
	addComponent(_powerStation);

	this -> updateShipHealth();
	this -> _shipDestroyed = false;

	stringw strShipHealth = "ship health: " + this -> getShipHealth();
	stringw strDefenceHealth = "Defence Station health: " + this -> _defenceStation -> getHealth();
	stringw strHelmHealth = "Helm Station health: " + this -> _helmStation -> getHealth();
	stringw strNavigationHealth = "Navigation Station health: " + this -> _navigationStation-> getHealth();
	stringw strPowerHealth = "Power Station health: " + this -> _powerStation -> getHealth();
	stringw strWeaponHealth = "Weapon Station health: " + this -> _weaponStation -> getHealth();

	this -> shipHealth =  env->addStaticText(strShipHealth.c_str(),rect<s32>(40, 80, 200, 100), false);
	this -> defenceStationHealth = env->addStaticText(strDefenceHealth.c_str(),rect<s32>(40,100, 200, 100), false);
	this -> helmStationHealth = env->addStaticText(strHelmHealth.c_str(),rect<s32>(40, 120, 200, 100), false);
	this -> navigationStationHealth = env->addStaticText(strNavigationHealth.c_str(),rect<s32>(40, 140, 200, 100), false);
	this -> powerStationHealth = env->addStaticText(strPowerHealth.c_str(),rect<s32>(40, 160, 200, 100), false);
	this -> weaponStationHealth = env->addStaticText(strWeaponHealth.c_str(),rect<s32>(40, 180, 200, 100), false);
}

Ship::~Ship(void)
{
	this->removeComponent(_defenceStation);
	this->removeComponent(_helmStation);
	this->removeComponent(_navigationStation);
	this->removeComponent(_weaponStation);
	this->removeComponent(_powerStation);
}

Station *Ship :: GetStation( STATION_TYPE s )
{
	this -> _defenceStation -> Damage( );

	switch( s )
	{
	case STATION_TYPE :: Defence:
		return this -> _defenceStation;
		break;
	case STATION_TYPE :: Helm:
		return this -> _helmStation;
		break;
	case STATION_TYPE :: Navigation:
		return this -> _navigationStation;
		break;
	//case STATION_TYPE :: Power:
	//	return this -> _powerStation;
	//	break;
	case STATION_TYPE :: Weapon:
		return this -> _weaponStation;
		break;
	};
	return NULL;
}

void Ship :: update()
{
	Entity :: update();
	this -> updateShipHealth();

	//updating the text for testing the health
	stringw strShipHealth = "ship health: " + this -> getShipHealth();
	stringw strDefenceHealth = "Defence Station health: " + this -> _defenceStation -> getHealth();
	stringw strHelmHealth = "Helm Station health: " + this -> _helmStation -> getHealth();
	stringw strNavigationHealth = "Navigation Station health: " + this -> _navigationStation-> getHealth();
	stringw strPowerHealth = "Power Station health: " + this -> _powerStation -> getHealth();
	stringw strWeaponHealth = "Weapon Station health: " + this -> _weaponStation -> getHealth();

	this -> shipHealth->setText(strShipHealth.c_str());
	this -> defenceStationHealth->setText(strDefenceHealth.c_str());
	this -> helmStationHealth->setText(strHelmHealth.c_str());
	this -> navigationStationHealth->setText(strNavigationHealth.c_str());
	this -> powerStationHealth->setText(strPowerHealth.c_str());
	this -> weaponStationHealth->setText(strWeaponHealth.c_str());

	if(this -> _shipHealth <= 0 && this -> _shipDestroyed == false)
	{
		this -> _shipDestroyed == true;
		
		//Game ends; Ship destroyed
		std::cout<< "Ship destroyed: " << this->getShipDestroyed() << "\n";	
	}
	if(this -> _helmStation -> getHealth() <= 0 && this -> _helmStation -> getStationDestroyed() == false)
	{
		this -> _helmStation -> setStationDestroyed(true);
		
		//Note players helmstation is gone
		std::cout<< "_helmStation destroyed: " << this->_helmStation->getStationDestroyed() << "\n";
	}
	if(this -> _defenceStation -> getHealth() <= 0 && this -> _defenceStation -> getStationDestroyed() == false)
	{
		this -> _defenceStation -> setStationDestroyed(true);
		
		//Note players defencestation is gone
		std::cout<< "_defenceStation destroyed: " << this->_defenceStation->getStationDestroyed() << "\n";
	}
	if(this -> _navigationStation -> getHealth() <= 0 && this -> _navigationStation -> getStationDestroyed() == false)
	{
		this -> _navigationStation -> setStationDestroyed(true);
		
		//Note players navigationstation is gone
		std::cout<< "_navigationStation destroyed: " << this->_navigationStation->getStationDestroyed() << "\n";
	}
	if(this -> _powerStation -> getHealth() <= 0 && this -> _powerStation -> getStationDestroyed() == false)
	{
		this -> _powerStation -> setStationDestroyed(true);
		
		//Note players powerstation is gone
		std::cout<< "_powerStation destroyed: " << this->_powerStation->getStationDestroyed() << "\n";
	}
	if(this -> _weaponStation -> getHealth() <= 0 && this -> _weaponStation -> getStationDestroyed() == false)
	{
		this -> _weaponStation -> setStationDestroyed(true);
		
		//Note players weaponstation is gone
		std::cout<< "_weaponStation destroyed: " << this->_weaponStation->getStationDestroyed() << "\n";
	}
}

void Ship :: updateShipHealth()
{
	this -> _shipHealth = 
		this -> _defenceStation -> getHealth() +
		this -> _helmStation -> getHealth() +
		this -> _navigationStation -> getHealth() +
		this -> _powerStation -> getHealth() +
		this -> _weaponStation -> getHealth();
}

void Ship :: draw()
{
	Entity :: draw();
	//env -> drawAll();
}

int Ship :: getShipHealth()
{
	return this -> _shipHealth;
}

bool Ship :: getShipDestroyed()
{
	return this -> _shipDestroyed;
}
