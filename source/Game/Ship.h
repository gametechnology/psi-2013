#ifndef ENTITY_SHIP
#define ENTITY_SHIP

#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"
#include "Irrlicht\irrlicht.h"

#include "Stations\Station.h"
#include "Engine/Entity.h"
#include "Player.h"

class DefenceStation;
class HelmStation;
class NavigationStation;
class PowerStation;
class WeaponStation;

class Ship : public Entity
{
public:
	//Player *players;
	DefenceStation		*_defenceStation;
	HelmStation			*_helmStation;
	NavigationStation	*_navigationStation;
	PowerStation		*_powerStation;
	WeaponStation		*_weaponStation;
	
	matrix4 inertiaMatrix;

	//to test the ship health and station health
	irr::gui::IGUIEnvironment *env;
	irr::gui::IGUIStaticText *shipHealth;
	irr::gui::IGUIStaticText *defenceStationHealth;
	irr::gui::IGUIStaticText *helmStationHealth;
	irr::gui::IGUIStaticText *navigationStationHealth;
	irr::gui::IGUIStaticText *powerStationHealth;
	irr::gui::IGUIStaticText *weaponStationHealth;

	int _shipHealth;
	bool _shipDestroyed;

	void init();
	void update();
	void updateShipHealth();
	void draw();

	void setInertiaMatrix(float h, float w, float d, float m);
	void Ship::handleMessage(unsigned int message, void* data);

	Ship(Composite * parent);
	virtual ~Ship(void);

	Station *GetStation(StationType );	

	int getShipHealth();
	bool getShipDestroyed();
private:
	stringw varToString(stringw str1, float var, stringw str2);
	stringw varToString(stringw str1, float var);
};
#endif