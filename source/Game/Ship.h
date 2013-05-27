#ifndef ENTITY_SHIP
#define ENTITY_SHIP

/*
* TODO Clearly a God-Class. This
* needs thorough refactoring.
*/


#include <Irrlicht/irrlicht.h>
#include <Engine/GameObject.h>
#include <Engine/CameraComponent.h>

#include "Player.h"
#include "Thruster.h"
#include "ShipMover.h"
#include "Laser.h"
#include "ObjectPool.h"
#include "HudHelpText.h"

#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"

class Ship : public GameObject, public INetworkListener
{
public:
	HudHelpText* help;

	//Player *players;
	DefenceStation		*_defenceStation;
	HelmStation			*_helmStation;
	NavigationStation	*_navigationStation;
	PowerStation		*_powerStation;
	WeaponStation		*_weaponStation;

	//to test the ship health and station health
	irr::gui::IGUIEnvironment *env;
	irr::gui::IGUIStaticText *shipHealth;
	irr::gui::IGUIStaticText *defenceStationHealth;
	irr::gui::IGUIStaticText *helmStationHealth;
	irr::gui::IGUIStaticText *navigationStationHealth;
	irr::gui::IGUIStaticText *powerStationHealth;
	irr::gui::IGUIStaticText *weaponStationHealth;
	
	Ship(irr::core::vector3df position, irr::core::vector3df rotation);
	virtual ~Ship();

	bool _shipDestroyed;

	bool _sitOnStation;

	void onAdd();
	void init();

	void update();
	void draw();

	void CheckChangeInput();

	Station* GetStation(StationType);
	Thruster** GetThrusters();

	int getShipHealth();
	bool getShipDestroyed();

	void SwitchToStation(StationType stationType);

	static ObjectPool<Laser>* laserPool;

	void fireLaser();
	
	void HandleNetworkMessage(NetworkPacket packet);
private:

	Station	*_currentStation;
	Thruster *_thrusters[4];
	irr::core::matrix4 *_inertiaMatrix;

	irr::core::stringw varToString(irr::core::stringw str1, float var, irr::core::stringw str2);
	irr::core::stringw varToString(irr::core::stringw str1, float var);

	void setInertiaMatrix(float h, float w, float d, float m);
};
#endif
