#include "HelmStation.h"

HelmStation::HelmStation(Ship *ship) : Station(ship)
{
	_stationType = ST_HELM;
	setStationDestroyed(false);

}

HelmStation::~HelmStation()
{
	Station::~Station();
}

void HelmStation::onAdd()
{
	Station::onAdd();
}

void HelmStation::init()
{
	Station::init();
	_stationTexture = game->driver->getTexture("../assets/Textures/Stations/HelmStation/helm_station.png");
	game->driver->makeColorKeyTexture(_stationTexture, irr::core::vector2d<irr::s32>(0, 0));
}
void HelmStation :: update( )
{
	Station::update();
	
	 NetworkPacket packet(SHIP_ACCELERATION);
	 packet << *_ship->transform->acceleration;
	 packet << *_ship->transform->angularAccelaration;
	 packet << *_ship->transform->position;
	 packet << *_ship->transform->rotation;
	 Network::GetInstance()->SendPacketToAllClients(packet, true);

	 
}

void HelmStation::update()
{
	Station::update();
}

void HelmStation::draw()
{
	Station::draw();

	game->driver->draw2DImage(_stationTexture,
		irr::core::vector2d<s32>(0, 0),
		irr::core::rect<s32>(0, 0, 1280, 720),
		0,
		irr::video::SColor(255, 255, 255, 255),
		true);
}

void HelmStation::enable()
{
	Station::enable();
}

void HelmStation::disable()
{
	Station::disable();
}
