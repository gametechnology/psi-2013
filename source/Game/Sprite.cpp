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
		rect<s32>(0, 0, _texture->getSize().Width, _texture->getSize().Height),
		0,
		SColor(255,255,255,255),
		true);
	}
}

void Sprite::setTexture(video::ITexture* texture)
{
	this->_texture = texture;
}

void Sprite::setPosition(position2d<s32> position)
{
	this->_position = position;
}