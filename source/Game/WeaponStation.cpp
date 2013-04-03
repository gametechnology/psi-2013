#include "WeaponStation.h"
#include "Engine\Game.h"
#include "Ship.h"
WeaponStation::WeaponStation(Composite* parent) : Entity(parent)
{
	cameramover = new WeaponCameraMover(this);

	this->_stationTexture = Game::driver->getTexture("../../assets/Textures/Stations/weapon station.png");
	Game::driver->makeColorKeyTexture(this->_stationTexture, position2d<s32>(0, 0));

	test = 0;
}

WeaponStation::~WeaponStation()
{
	Entity::~Entity();
}

void WeaponStation::update()
{
	test++;
	if(test == 1000)
	{
		shoot();
		test = 0;
	}
	Entity::update();
}

void WeaponStation::draw()
{
	Game::driver->draw2DImage(this->_stationTexture,
		position2d<s32>(0,0),
		rect<s32>(0,0,1280,720),
		0,
		SColor(255,255,255,255),
		true);

	Entity::draw();
}

void WeaponStation::shoot()
{
	scene::ISceneManager* sm = Game::device->getSceneManager();
	scene::ICameraSceneNode* camera = sm->getActiveCamera();

	// get line of camera

	core::vector3df start = camera->getPosition();
	core::vector3df end = (camera->getTarget() - start);
	end.normalize();
	start += end*8.0f;
	end = start + (end * camera->getFarValue());

	start = camera->getPosition();
	end = (camera->getTarget() - start);
	end.normalize();
	start += end*8.0f;
	end = start + (end * camera->getFarValue());

	// create fire ball
	scene::ISceneNode* node = 0;
	node = sm->addBillboardSceneNode(0,
		core::dimension2d<f32>(25,25), start);

	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialTexture(0, Game::device->getVideoDriver()->getTexture("../../assets/Textures/fireball.bmp"));
	node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	f32 length = (f32)(end - start).getLength();
	const f32 speed = 0.6f;
	u32 time = (u32)(length / speed);

	scene::ISceneNodeAnimator* anim = 0;

	// set flight line

	anim = sm->createFlyStraightAnimator(start, end, time);
	node->addAnimator(anim);
	anim->drop();

	anim = sm->createDeleteAnimator(time);
	node->addAnimator(anim);
	anim->drop();
}