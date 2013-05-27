#ifndef STATION_BASE
#define STATION_BASE

#include "../Player.h"

/*
* TODO An object is either a Component
* or a GameObject, not both. Make a choice
* and refactor accordingly.
*/
#include <Engine/GameObject.h>
#include <Engine/Component.h>
#include <Engine/Core.h>
#include <Irrlicht/irrlicht.h>

// Use constants over Defines.
const float STUN_TIME = 4.0f;

class Ship;
class HealthComponent;
class PowerComponent;
class ShieldComponent;

enum StationType
{
	ST_POWER		= 0,
	ST_DEFENCE		= 1,
	ST_WEAPON		= 2,
	ST_HELM		= 3,
	ST_NAVIGATION	= 4
};

class Station : public Component
{
public:
	Station( Ship *ship, int startHealth );
	Station( Ship *ship );
	virtual ~Station(void);

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

	virtual void onAdd();
	virtual void init();
	virtual void update();
	virtual void draw();

	virtual void OnDamage( );
	virtual void OnEnabled() = 0;
	virtual void OnDisabled() = 0;

	void leaveStation(StationType station);

	HudComposite* hud;
	StationType _stationType;
protected:
	video::IVideoDriver *driver;

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