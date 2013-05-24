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
		node->setPosition(this->parent->transform->position->operator+(*this->transform->position));
		node->setRotation(this->parent->transform->rotation->operator+(*this->transform->rotation));
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