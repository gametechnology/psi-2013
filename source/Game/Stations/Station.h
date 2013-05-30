#ifndef STATION_BASE
#define STATION_BASE

/*
* TODO An object is either a Component
* or a GameObject, not both. Make a choice
* and refactor accordingly.
*/
#include <Engine/GameObject.h>
#include <Engine/Component.h>
#include <Engine/Core.h>
#include <Irrlicht/irrlicht.h>

#include "../Player.h"
#include "../HudComposite.h"
#include "../HealthComponent.h"
#include "../PowerComponent.h"
#include "../ShieldComponent.h"

class Ship;

// Use constants over Defines.
const float STUN_TIME = 4.0f;

enum StationType
{
	ST_NONE			= -1,
	ST_POWER		= 0,
	ST_DEFENCE		= 1,
	ST_WEAPON		= 2,
	ST_HELM			= 3,
	ST_NAVIGATION	= 4,
};

class Station : public Composite
{
public:
	Station(Core*, Interface*, Ship*, int startHealth);
	Station(Core*, Interface*, Ship*);
	virtual ~Station(void);

	virtual void enable();
	virtual void disable();

	StationType GetStationType();
	bool SwitchTimePassed();
	bool IsStunned();

	bool HasPower();
	bool HasShield();

	/*
	* Set the player for occupating this station.
	*
	* @return boolean
	* The returned boolean tells you if the set was succesfull or not. It will
	* fail if the station is already occupied.
	*/
	bool setPlayerOccupation(Player* player);
	/*
	* Resets the station it's occupation. Simultaneously setting the player pointer
	* and occupied boolean to NULL and 'false' respectively.
	*/
	void resetPlayerOccupation();

	std::string helpTextString;

	bool getStationDestroyed();
	void setStationDestroyed(bool _destroyed);

	int getHealth();
	void updateHealth();
	void increaseHealth(int health);
	void decreaseHealth(int health);


	int getPower();
	void updatePower(int power);
	void increasePower(int power);
	void decreasePower(int power);

	void repairStation(int health);
	void handleMessage(unsigned int message, void* data);

	virtual void init();
	virtual void update();
	virtual void draw();

	virtual void OnDamage();

	void leaveStation(StationType station);

	HudComposite* hud;
	StationType _stationType;
protected:
	Core* _core;
	Interface* _interface;

	irr::video::IVideoDriver *driver;

	Ship	*_ship;
	Player	*_player;

	time_t *_switchTime;			//the time that the player switched to this station
	time_t *_playerOnStationTime;	//the time that the player has spent on this station (since he switched)
	time_t *_stunTime;				//if a station fot stunned, the time it happened will be stored here.
private:
	int _tempTimer;
	int _totalHealth;
	HealthComponent* _healthComponent;
	PowerComponent* _powerComponent;
	ShieldComponent* _shieldComponent;
	bool _stationDestroyed;
	bool _isOccupied;
};
#endif