#ifndef STATION_BASE
#define STATION_BASE

#include "../HudComposite.h"
#include "../Player.h"

#include <Engine/Entity.h>
#include <Engine/Component.h>
#include <Engine/Game.h>
#include <Irrlicht/irrlicht.h>

#define STUN_TIME 4.0
class Ship;
class HealthComponent;
class PowerComponent;
class ShieldComponent;

enum StationType
{
	ST_NONE			= -1,
	ST_POWER		= 0,
	ST_DEFENCE		= 1,
	ST_WEAPON		= 2,
	ST_HELM			= 3,
	ST_NAVIGATION	= 4,
};

class Station : public Entity
{
	void leaveStation(StationType station);

public:
	Station( Ship *ship, int startHealth );
	Station( Ship *ship );
	virtual ~Station(void);

	StationType GetStationType();
	bool SwitchTimePassed();
	bool IsStunned();

	bool HasPower();
	bool HasShield();

	// This
	std::list<Player*> playerlist;

	StationType _occupiedStation;

	/*
	* Set the player for occupating this station.
	*
	* @return boolean
	* The returned boolean tells you if the set was succesfull or not. It will
	* fail if the station is already occupied.
	*/
	bool setPlayerOccupation(Player* player);
	// because all the player stuff in networking is broken, we'll just do things manually temporarily:
	bool setStationOccupation();
	/*
	* Resets the station it's occupation. Simultaneously setting the player pointer
	* and occupied boolean to NULL and 'false' respectively.
	*/
	void resetPlayerOccupation();
	// the above doesn't work due to player stuff being broken, so again manually:
	void resetStationOccupation();

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