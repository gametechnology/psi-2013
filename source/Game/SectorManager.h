#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include "Engine/Component.h"
#include "SectorTemplate.h"
#include "GalaxyMap.h"
#include "MapSector.h"
#include "NetworkInterface.h"
#include "Ship.h"


class SectorManager : public Component, public INetworkListener {
public:
	SectorManager(GalaxyMap* map,Ship* ship);
	void handleMessage(unsigned int message, void* data = 0);
	void onAdd();
	virtual ~SectorManager();
	MapSector* _mapSector;
	char* activeSceneName;
	Ship* getShip();

	virtual void HandleNetworkMessage(NetworkPacket packet);
	friend sf::Packet& operator <<(sf::Packet& out, MapSector& in);
	friend sf::Packet& operator >>(sf::Packet& in, MapSector& out);
private:
	GalaxyMap* _map;
	Ship* _ship;
	void SearchNextMapSector(int currMapId, int connectionId);
	void SetNextSector(MapSector& nextsector);
	MapSector* SearchMapSector(int currMapId);
};

#endif
