#include "Mist.h"

using namespace irr;
using namespace irr::video;

Mist::Mist(Core* core, SColor color, float nearDistance, float farDistance, E_FOG_TYPE fogType) : GameObject()
{
	_core = core;
	_color = color;
	_nearDistance = nearDistance;
	_farDistance = farDistance;
	_fogType = fogType;
}

void Mist::init() {
	_core->getDriver()->setFog(_color, _fogType, _nearDistance, _farDistance);
}

void Mist::update()
{
	if (_valueChanged) 
	{
		_valueChanged = false;
		_core->getDriver()->setFog(_color, _fogType, _nearDistance, _farDistance);
	}
}

void Mist::setColor(video::SColor color) 
{
	_valueChanged = true;
	_color = color;
}

void Mist::setNearDistance(float nearDistance) 
{
	_valueChanged = true;
	_nearDistance = nearDistance;
}

void Mist::setFarDistance(float farDistance)
{
	_valueChanged = true;
	_farDistance = farDistance;
}

void Mist::setFogType(video::E_FOG_TYPE fogType) 
{
	_valueChanged = true;
	_fogType = fogType;
}

Mist::~Mist(void)
{
	_core->getDriver()->setFog();
}