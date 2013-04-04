#include "Skybox.h"
#include "Messages.h"

Skybox::Skybox(const io::path & filePath,Composite* parent) : Entity(parent) {
	_filePath = "../assets/Textures/SkyBoxes/";
	_filePath += filePath;
	//printf(filePath.c_str());
	init();
}
void Skybox::init(){
	Game::getSceneManager()->addSkyDomeSceneNode(Game::driver->getTexture(_filePath),128,128,0.99999f,10.0f,2000.0f);
}
Skybox::~Skybox() {
	Entity::~Entity();
}
