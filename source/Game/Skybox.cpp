#include "Skybox.h"
#include "Messages.h"

Skybox::Skybox( const io::path & filePath ) : Entity() {
	_filePath = "../assets/Textures/SkyBoxes/";
	_filePath += filePath;
	//printf(filePath.c_str());
}

void Skybox::init() {
	skydome = scene->getIrrlichtSceneManager()->addSkyDomeSceneNode(game->driver->getTexture(_filePath), 128, 128, 0.99999f, 10.0f, 1000.0f);
	skydome->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	skydome->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

	Entity::init();
}

Skybox::~Skybox() {
	skydome->remove();
	//delete skydome;
	Entity::~Entity();
}
