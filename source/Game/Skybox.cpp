#include "Skybox.h"
#include "Messages.h"

Skybox::Skybox(const io::path & filePath,Composite* parent) : Entity(parent) {
	this->node = Game::getSceneManager()->addSkyDomeSceneNode(Game::driver->getTexture(filePath),128,128,0.99999f,10.0f,2000.0f);
}

Skybox::~Skybox() {
	Entity::~Entity();
}
