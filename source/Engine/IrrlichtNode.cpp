#include "Engine\IrrlichtNode.h"
#include "Engine\Game.h"

IrrlichtNode::IrrlichtNode(std::string modelPath) : Component() {

}

void IrrlichtNode::createNode(std::string modelPath) {
	// Get the mesh
	irr::scene::IAnimatedMesh* mesh = Game::getSceneManager()->getMesh(modelPath.c_str());

	// Create model entity
	node = Game::getSceneManager()->addMeshSceneNode( mesh );
}

void IrrlichtNode::update() {

}

IrrlichtNode::~IrrlichtNode() {
	if (node != NULL) {
		node->drop();
	}
}