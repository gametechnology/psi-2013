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

	//ShipMover* mover = new ShipMover(_ship); // Ship mover with thrusters.
	BasicShipMover* mover = new BasicShipMover(_ship); // Ship mover without thrusters.
	addComponent(mover);
}

void HelmStation::init()
{
	Station::init();
	_stationTexture = game->driver->getTexture("../assets/Textures/Stations/HelmStation/helm_station.png");
	game->driver->makeColorKeyTexture(_stationTexture, irr::core::vector2d<irr::s32>(0, 0));
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
	((Ship*)parent)->help->setHelpText(L"Forward: 'R'\nBackwards: 'F'\nRoll left: 'Q'\nRoll right: 'E'\nPitch up: 'W'\nPitch down: 'S'\nJaw left: 'A'\nJaw right: 'D'\ntodo: Exit station: 'Esc'");

	Station::enable();
}

void HelmStation::disable()
{
	Station::disable();
}
