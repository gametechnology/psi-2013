#ifndef SPRITE_H
#define SPRITE_H

#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"

class Sprite : public Entity {
public:
	Sprite();
	virtual ~Sprite();

	virtual void draw();
	virtual void setTexture(irr::video::ITexture* texture);
private:
	irr::video::ITexture* _texture;
	irr::core::rect<irr::s32> _size;
};

#endif // SPRITE_H