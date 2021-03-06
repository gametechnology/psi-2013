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
		node->setPosition(this->parent->transform->position+(this->transform->position));
		node->setRotation(this->parent->transform->rotation+(this->transform->rotation));
		node->setVisible(this->parent->enabled);
	}

	Entity::update();
}

void IrrlichtNode::setVisible(bool isVisible)
{
	this->node->setVisible(isVisible);
}

IrrlichtNode::~IrrlichtNode() {
	if (node != NULL) {
		this->scene->getIrrlichtSceneManager()->addToDeletionQueue(node);
		node = NULL;
	}
	Entity::~Entity();
}