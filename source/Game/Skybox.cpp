#include "Skybox.h"
#include "Messages.h"

Skybox::Skybox(const io::path & filePath,Composite* parent) : Entity() {
	_filePath = "../assets/Textures/SkyBoxes/";
	_filePath += filePath;
	//printf(filePath.c_str());
}

void Skybox::init(){
	irr::scene::ISceneNode * skydome = scene->sceneManager->addSkyDomeSceneNode(game->driver->getTexture(_filePath),128,128,0.99999f,10.0f,1000.0f);
	skydome->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	skydome->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
}

Skybox::~Skybox() {
	Entity::~Entity();
}
