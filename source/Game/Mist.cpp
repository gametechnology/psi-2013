#include "Mist.h"

Mist::Mist(video::SColor color, float nearDistance, float farDistance, video::E_FOG_TYPE fogType) : Entity()
{
	_color = color;
	_nearDistance = nearDistance;
	_farDistance = farDistance;
	_fogType = fogType;
}

void Mist::init() {
	game->driver->setFog(_color, _fogType, _nearDistance, _farDistance);
}

void Mist::update()
{
	if (_valueChanged) 
	{
		_valueChanged = false;
		game->driver->setFog(_color, _fogType, _nearDistance, _farDistance);
	}
}

void Mist::SetColor(video::SColor color) 
{
	_valueChanged = true;
	_color = color;
}

void Mist::SetNearDistance(float nearDistance) 
{
	_valueChanged = true;
	_nearDistance = nearDistance;
}

void Mist::SetFarDistance(float farDistance)
{
	_valueChanged = true;
	_farDistance = farDistance;
}

void Mist::SetFogType(video::E_FOG_TYPE fogType) 
{
	_valueChanged = true;
	_fogType = fogType;
}

Mist::~Mist(void)
{
	game->driver->setFog();
}