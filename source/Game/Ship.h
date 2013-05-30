#ifndef ENTITY_SHIP
#define ENTITY_SHIP

/*
* TODO Clearly a God-Class. This
* needs thorough refactoring.
*/

#include <Irrlicht/irrlicht.h>
#include <Engine/Core.h>
#include <Engine/GameObject.h>
#include <Engine/CameraComponent.h>
#include <Engine/MeshComponent.h>
#include <Engine/Interface.h>

#include "Player.h"
#include "Thruster.h"
#include "Laser.h"
#include "ObjectPool.h"

#include "Stations\Station.h"

#include "SendAndReceivePackets.h"
#include "HudHelpText.h"

class DefenceStation;
class HelmStation;
class NavigationStation;
class PowerStation;
class WeaponStation;

class Ship : public GameObject, public INetworkListener
{
public:
	HudHelpText* help;

	DefenceStation *_defenceStation;
	HelmStation *_helmStation;
	NavigationStation *_navigationStation;
	PowerStation *_powerStation;
	WeaponStation *_weaponStation;

	//to test the ship health and station health
	irr::gui::IGUIEnvironment *env;
	irr::gui::IGUIStaticText *shipHealth;
	irr::gui::IGUIStaticText *defenceStationHealth;
	irr::gui::IGUIStaticText *helmStationHealth;
	irr::gui::IGUIStaticText *navigationStationHealth;
	irr::gui::IGUIStaticText *powerStationHealth;
	irr::gui::IGUIStaticText *weaponStationHealth;
	
	Ship(Core*, Interface*, irr::core::vector3df position, irr::core::vector3df rotation);
	virtual ~Ship();

	bool _shipDestroyed;

	bool _sitOnStation;

	virtual void init();

	virtual void update();
	virtual void draw();

	void CheckChangeInput();

	Station* GetStation(StationType);
	Thruster** GetThrusters();

	int getShipHealth();
	bool getShipDestroyed();

	void SwitchToStation(StationType stationType, Player*);

	static ObjectPool<Laser>* laserPool;

	void fireLaser();
	
	virtual void handleMessage(unsigned int, void* data = 0) { };
	virtual void handleNetworkMessage(NetworkPacket packet);
private:
	Core* _core;
	Interface* _interface;

	MeshComponent* _mesh;

	Station	*_currentStation;
	Thruster *_thrusters[4];
	irr::core::matrix4 *_inertiaMatrix;

	irr::core::stringw varToString(irr::core::stringw str1, float var, irr::core::stringw str2);
	irr::core::stringw varToString(irr::core::stringw str1, float var);

	void setInertiaMatrix(float h, float w, float d, float m);
};

#endif
