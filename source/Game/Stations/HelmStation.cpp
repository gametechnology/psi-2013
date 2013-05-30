#include "HelmStation.h"

using namespace irr;

HelmStation::HelmStation(Core* core, Interface* ui, Ship *ship) : Station(core, ui, ship)
{
	_core = core;
	_interface = ui;
	_stationType = ST_HELM;
	setStationDestroyed(false);
}

HelmStation::~HelmStation()
{
}

void HelmStation::init()
{
	Station::init();
}


void HelmStation::update()
{
	_ship->setPosition(_core->getSmgr()->getActiveCamera()->getPosition());
	_ship->setRotation(_core->getSmgr()->getActiveCamera()->getRotation());

	Station::update();
}

void HelmStation::draw()
{
	Station::draw();
}

void HelmStation::enable()
{
	(_ship)->help->setHelpText(L"Forward: 'W'\nBackwards: 'S'\nRoll left: 'A'\nRoll right: 'D'\nPitch up: 'down'\nPitch down: 'up'\nJaw left: 'left'\nJaw right: 'right'\ntodo: Exit station: 'Esc'");
	
	_interface->addImage("../assets/Textures/Stations/HelmStation/helm_station.png", 0, 0);

	_helmCamera = new CameraComponent(_core->getSmgr(), CameraComponent::FIRST_PERSON);
	_helmCamera->init();

	addComponent(_helmCamera);

	Station::enable();
}

void HelmStation::disable()
{
	_interface->resetInterface();
	Station::disable();
}
