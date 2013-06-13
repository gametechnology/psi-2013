#include "Sprite.h"
#include "Engine\Game.h"

Sprite::Sprite() : Entity() {

}

Sprite::~Sprite()
{
	Entity::~Entity();
}

void Sprite::draw()
{
	if(_texture != 0)
	{
		irr::core::position2d<irr::s32> twodposition = irr::core::position2d<irr::s32>(transform->position.X, transform->position.Y);

		game->driver->draw2DImage(_texture,
		twodposition,
		irr::core::rect<irr::s32>(0, 0, _texture->getSize().Width, _texture->getSize().Height),
		0,
		video::SColor(255,255,255,255),
		true);
	}
}

void Sprite::setTexture(video::ITexture* texture)
{
	this->_texture = texture;
}