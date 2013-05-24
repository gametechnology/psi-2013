#include "Engine\IrrlichtNode.h"
#include "Engine\Game.h"

IrrlichtNode::IrrlichtNode(const irr::io::path& modelPath) : Entity() {
	this->modelPath = modelPath;
	this->node = NULL;
}

void IrrlichtNode::init() {
	createNode();

	Entity::init();
}

void IrrlichtNode::createNode() {
	// Get the mesh
	irr::scene::IAnimatedMesh* mesh = this->scene->getIrrlichtSceneManager()->getMesh( modelPath );
	// Create model entity
	node = this->scene->getIrrlichtSceneManager()->addMeshSceneNode( mesh );
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void IrrlichtNode::update() {
	if (node != NULL) {
		node->setPosition(*this->transform->position);
		node->setRotation(*this->transform->rotation);
		node->setVisible(this->parent->enabled);
	}

	Entity::update();
}

IrrlichtNode::~IrrlichtNode() {
	if (node != NULL) {
		node->remove();
		//delete node;
	}
	Entity::~Entity();
}