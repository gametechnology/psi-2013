#include "HelmStation.h"

using namespace irr;

HelmStation::HelmStation(Core* core, Interface* ui, Ship *ship) : Station(core, ui, ship)
{
	_core = core;
	_stationType = ST_HELM;
	setStationDestroyed(false);
}

HelmStation::~HelmStation()
{
	Station::~Station();
}

void HelmStation::init()
{
	BasicShipMover* mover = new BasicShipMover(_core, _ship); // Ship mover without thrusters.
	addComponent(mover);
	
	_stationTexture = _core->getDriver()->getTexture("../assets/Textures/Stations/HelmStation/helm_station.png");
	_core->getDriver()->makeColorKeyTexture(_stationTexture, irr::core::vector2d<irr::s32>(0, 0));

	Station::init();
}


void HelmStation::update()
{
	Station::update();
}

void HelmStation::draw()
{
	_core->getDriver()->draw2DImage(_stationTexture,
		irr::core::vector2d<s32>(0, 0),
		irr::core::rect<s32>(0, 0, 1280, 720),
		0,
		irr::video::SColor(255, 255, 255, 255),
		true);

	Station::draw();
}

void HelmStation::enable()
{
	(_ship)->help->setHelpText(L"Forward: 'W'\nBackwards: 'S'\nRoll left: 'A'\nRoll right: 'D'\nPitch up: 'down'\nPitch down: 'up'\nJaw left: 'left'\nJaw right: 'right'\ntodo: Exit station: 'Esc'");

	Station::enable();
}

void HelmStation::disable()
{
	Station::disable();
}
