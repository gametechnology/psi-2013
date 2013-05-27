#ifndef SPRITE_H
#define SPRITE_H

#include <Engine/Core.h>
#include <Engine/GameObject.h>
#include <Irrlicht/irrlicht.h>

class Sprite : public GameObject
{
public:
	Sprite(Core* core);
	virtual ~Sprite();

	virtual void draw();
	virtual void setTexture(irr::video::ITexture* texture);
private:
	irr::video::ITexture* _texture;
	irr::core::rect<irr::s32> _size;

	Core* _core;
};

#endif // SPRITE_H