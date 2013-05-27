#include "Sprite.h"

using namespace irr;
using namespace irr::core;

Sprite::Sprite(Core* core) : GameObject() 
{
	_core = core;
}

Sprite::~Sprite()
{
	
}

void Sprite::draw()
{
	if(_texture != 0)
	{
		position2d<s32> twodposition = position2d<s32>(_position->X, _position->Y);

		_core->getDriver()->draw2DImage(_texture, twodposition,	rect<s32>(0, 0, _texture->getSize().Width, _texture->getSize().Height),
		0, video::SColor(255,255,255,255), true);
	}
}

void Sprite::setTexture(video::ITexture* texture)
{
	this->_texture = texture;
}