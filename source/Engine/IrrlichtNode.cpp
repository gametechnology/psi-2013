#include "Engine\IrrlichtNode.h"
#include "Engine\Game.h"

IrrlichtNode::IrrlichtNode(const irr::io::path& modelPath) : Component() {
	this->modelPath = modelPath;
	this->node = NULL;
}

void IrrlichtNode::init() {
	createNode();

	Component::init();
}

void IrrlichtNode::createNode() {
	// Get the mesh
	irr::scene::IAnimatedMesh* mesh = Component::getScene()->getIrrlichtSceneManager()->getMesh( modelPath );

	// Create model entity
	node = getScene()->getIrrlichtSceneManager()->addMeshSceneNode( mesh );
}

void IrrlichtNode::update() {
	if (node != NULL) {
		node->setPosition(*entity->transform->position);
		node->setRotation(*entity->transform->rotation);
	}

	Component::update();
}

IrrlichtNode::~IrrlichtNode() {
	if (node != NULL) {
		node->drop();
		delete node;
	}
}