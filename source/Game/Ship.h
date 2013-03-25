#ifndef SHIP
#define SHIP

#include "Engine\Entity.h"
#include "Player.h"

/*#include "Stations\Station.h"
#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"*/

class Ship  : public Entity {
private:
	Player *players;

	/*DefenceStation		*_defenceStation;
	HelmStation			*_helmStation;
	NavigationStation	*_navigationStation;
	PowerStation		*_powerStation;
	WeaponStation		*_weaponStation;*/

public:
	Ship(Composite * parent);
	~Ship(void);

	//DefenceStation*	GetDefenceStation() { return _defenceStation; }
	//PowerStation*	GetPowerStation()	{ return _powerStation; }
};

#endif

