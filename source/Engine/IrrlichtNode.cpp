#include "Engine\IrrlichtNode.h"
#include "Engine\Game.h"

IrrlichtNode::IrrlichtNode(const irr::io::path& modelPath) : Component() {
	*this->modelPath = modelPath;
}

void IrrlichtNode::init() {
	createNode();
}

void IrrlichtNode::createNode() {
	// Get the mesh
	irr::scene::IAnimatedMesh* mesh = Component::getGame()->getSceneManager()->getMesh( &modelPath );

	// Create model entity
	node = Component::getGame()->getSceneManager()->addMeshSceneNode( mesh );
}

void IrrlichtNode::update() {
	node->setPosition(*Component::entity->transform->position);
	node->setRotation(*Component::entity->transform->rotation);
}

IrrlichtNode::~IrrlichtNode() {
	if (node != NULL) {
		node->drop();
		delete node;
	}
}