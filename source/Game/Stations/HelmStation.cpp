#include "HelmStation.h"

BasicShipMover* mover;

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
	mover = new BasicShipMover(_ship); // Ship mover without thrusters.
	addComponent(mover);
}

void HelmStation::init()
{
	Station::init();
	_stationTexture = game->driver->getTexture("../assets/Textures/Stations/HelmStation/helm_station.png");
	game->driver->makeColorKeyTexture(_stationTexture, irr::core::vector2d<irr::s32>(0, 0));
}


//TODO: remove debug variables
bool ding = false;
float temp = 0;
void HelmStation::update()
{
	if (this->game->input->isKeyboardButtonPressed(KEY_KEY_I))
	{
		ding = !ding;
	}	
	if (ding) {
		if (this->game->input->isKeyboardButtonDown(irr::KEY_KEY_9)) {
			temp += 0.1f;
		} else if  (this->game->input->isKeyboardButtonDown(irr::KEY_KEY_8)) {
			temp -= 0.1f;
			if (temp <= 0) temp = 0;
		}
		mover->setMaxSpeed(temp);
	} else {
		mover->setMaxSpeed((float)getPower() / 100); //This is the only line of code that should stay
	}

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
	((Ship*)parent)->help->setHelpText(L"Forward: 'W'\nBackwards: 'S'\nRoll left: 'A'\nRoll right: 'D'\nPitch up: 'down'\nPitch down: 'up'\nJaw left: 'left'\nJaw right: 'right'\ntodo: Exit station: 'Esc'");

	Station::enable();
}

void HelmStation::disable()
{
	Station::disable();
}
