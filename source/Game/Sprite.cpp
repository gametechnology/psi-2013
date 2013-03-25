#include "Sprite.h"
#include "Engine\Game.h"

Sprite::Sprite(Composite* parent) : Entity(parent)
{
}

Sprite::~Sprite()
{
	Entity::~Entity();
}

void Sprite::draw()
{
	if(_texture != 0)
	{
		Game::driver->draw2DImage(this->_texture,
		_position,
		_size,
		0,
		SColor(255,255,255,255),
		true);
	}
}

void Sprite::setTexture(video::ITexture* texture, rect<s32> size)
{
	this->_texture = texture;
	this->_size = size;
}

void Sprite::setPosition(position2d<s32> position)
{
	this->_position = position;
}