#include "Engine\IrrlichtNode.h"

void Entity::createNode(std::string modelPath) {
	// Get the mesh
	irr::scene::IAnimatedMesh* mesh = Game::getSceneManager()->getMesh(modelPath.c_str());

	// Create model entity
	this->node =  Game::getSceneManager()->addMeshSceneNode( mesh );
}

Entity::~Entity() {
	Composite::~Composite();
	if (node != NULL)
	{
		node->drop();
	}
}