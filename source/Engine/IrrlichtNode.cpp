#include "Engine\IrrlichtNode.h"
#include "Engine\Game.h"

IrrlichtNode::IrrlichtNode(const irr::io::path& modelPath) : Entity() {
	this->modelPath = modelPath;
	this->node = NULL;
}

void IrrlichtNode::init() {
	printf("[IrrlichtNode]-init \n");
	createNode();

	Entity::init();
}

void IrrlichtNode::createNode() {
	printf("[IrrlichtNode]-CreateNode \n");
	// Get the mesh
	irr::scene::IAnimatedMesh* mesh = this->scene->getIrrlichtSceneManager()->getMesh( modelPath );
	// Create model entity
	node = this->scene->getIrrlichtSceneManager()->addMeshSceneNode( mesh );
}

void IrrlichtNode::update() {
	if (node != NULL) {
	printf("[IrrlichtNode]-update \n");
		node->setPosition(*this->parent->transform->position);
		node->setRotation(*this->parent->transform->rotation);
	}

	Entity::update();
}

IrrlichtNode::~IrrlichtNode() {
	if (node != NULL) {
		node->drop();
		delete node;
	}
	Entity::~Entity();
}