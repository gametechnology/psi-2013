#ifndef SPRITE_H
#define SPRITE_H

#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"

class Sprite : public Entity
{
public:
	Sprite(Composite* parent);
	virtual ~Sprite();

	virtual void draw();
	virtual void setTexture(video::ITexture* texture, rect<s32> size);
	virtual void setPosition(position2d<s32> position);
private:
	video::ITexture* _texture;
	rect<s32> _size;
	position2d<s32> _position;
};

#endif // SPRITE_H