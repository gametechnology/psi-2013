#include "Ship.h"
#include "Stations/Station.h"

Ship::Ship( Composite * parent ) : Entity ( parent )
{
	this->env = Game :: device->getGUIEnvironment();

	//TODO remove temp stuff
	this->_defenceStation		= new DefenceStation( this );
	this->_helmStation		= new HelmStation( this );
	this->_navigationStation	= new NavigationStation( this );
	this->_weaponStation		= new WeaponStation( this );
	this->_powerStation		= new PowerStation( this );
	
	this->_defenceStation		-> Initialize();
	this->_helmStation		-> Initialize();
	this->_navigationStation	-> Initialize();
	this->_weaponStation		-> Initialize();
	this->_powerStation		-> Initialize();
	
	addComponent(_defenceStation);
	addComponent(_helmStation);
	addComponent(_navigationStation);
	addComponent(_weaponStation);
	addComponent(_powerStation);

	this->updateShipHealth();
	this->_shipDestroyed = false;

	stringw strShipHealth = "ship health: " + this->getShipHealth();
	stringw strDefenceHealth = "Defence Station health: " + this->_defenceStation->getHealth();
	stringw strHelmHealth = "Helm Station health: " + this->_helmStation->getHealth();
	stringw strNavigationHealth = "Navigation Station health: " + this->_navigationStation-> getHealth();
	stringw strPowerHealth = "Power Station health: " + this->_powerStation->getHealth();
	stringw strWeaponHealth = "Weapon Station health: " + this->_weaponStation->getHealth();


	this->shipHealth				= env->addStaticText(strShipHealth.c_str(),			rect<s32>(40,  80, 300, 100), false);	this->shipHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->defenceStationHealth		= env->addStaticText(strDefenceHealth.c_str(),		rect<s32>(40, 100, 300, 120), false);	this->defenceStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->helmStationHealth			= env->addStaticText(strHelmHealth.c_str(),			rect<s32>(40, 120, 300, 140), false);	this->helmStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->navigationStationHealth	= env->addStaticText(strNavigationHealth.c_str(),	rect<s32>(40, 140, 300, 160), false);	this->navigationStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->powerStationHealth		= env->addStaticText(strPowerHealth.c_str(),		rect<s32>(40, 160, 300, 180), false);	this->powerStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
	this->weaponStationHealth		= env->addStaticText(strWeaponHealth.c_str(),		rect<s32>(40, 180, 300, 200), false);	this->weaponStationHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

}

Ship::~Ship(void)
{
	this->removeComponent(_defenceStation);
	this->removeComponent(_helmStation);
	this->removeComponent(_navigationStation);
	this->removeComponent(_weaponStation);
	this->removeComponent(_powerStation);
}

Station *Ship :: GetStation( StationType s )
{
	this->_defenceStation->Damage( );

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
	//case STATION_TYPE :: Power:
	//	return this->_powerStation;
	//	break;
	case ST_WEAPON:
		return this->_weaponStation;
		break;
	};
	return NULL;
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

void Ship :: update()
{
	Entity :: update();
	this->updateShipHealth();

	//updating the text for testing the health
	stringw strShipHealth = "ship health: " + this->getShipHealth();
	stringw strDefenceHealth = "Defence Station health: " + this->_defenceStation->getHealth();
	stringw strHelmHealth = "Helm Station health: " + this->_helmStation->getHealth();
	stringw strNavigationHealth = "Navigation Station health: " + this->_navigationStation-> getHealth();
	stringw strPowerHealth = "Power Station health: " + this->_powerStation->getHealth();
	stringw strWeaponHealth = "Weapon Station health: " + this->_weaponStation->getHealth();

	this->shipHealth->setText(				(varToString("Ship HP : ",		this->getShipHealth())					).c_str());
	this->defenceStationHealth->setText(	(varToString("Defence HP: ",	this->_defenceStation->getHealth())		).c_str());
	this->helmStationHealth->setText(		(varToString("Helm HP: ",		this->_helmStation->getHealth())		).c_str());
	this->navigationStationHealth->setText(	(varToString("Navigation HP: ",	this->_navigationStation->getHealth())	).c_str());
	this->powerStationHealth->setText(		(varToString("Power HP: ",		this->_powerStation->getHealth())		).c_str());
	this->weaponStationHealth->setText(		(varToString("Weapon HP: ",		this->_weaponStation->getHealth())		).c_str());

	//TODO! Stations need a way to leave. Set _sitOnStation on false. Temporary code, other team should make a better version of it someday.
	if(_sitOnStation==false&&Game::input->isKeyboardButtonPressed(KEY_KEY_1)){
		this -> _defenceStation		-> Initialize();
		_sitOnStation=true;
	} else 
	if(_sitOnStation==false&&Game::input->isKeyboardButtonPressed(KEY_KEY_2)){
		this -> _helmStation		-> Initialize();
		_sitOnStation=true;
	}else 
	if(_sitOnStation==false&&Game::input->isKeyboardButtonPressed(KEY_KEY_3)){
		this -> _navigationStation		-> Initialize();
		_sitOnStation=true;
	}else 
	if(_sitOnStation==false&&Game::input->isKeyboardButtonPressed(KEY_KEY_4)){
		this -> _weaponStation		-> Initialize();
		_sitOnStation=true;
	}else 
	if(_sitOnStation==false&&Game::input->isKeyboardButtonPressed(KEY_KEY_5)){
		this -> _powerStation		-> Initialize();
		_sitOnStation=true;
	}

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

	if(this->_powerStation->getHealth() <= 0 && this->_powerStation->getStationDestroyed() == false) {
		this->_powerStation->setStationDestroyed(true);
	}

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
		this->_powerStation->getHealth() +
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
