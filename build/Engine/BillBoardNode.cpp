#include "Engine\BillBoardNode.h"
#include <Engine\Game.h>

BillBoardNode::BillBoardNode( const irr::io::path& modelPath, irr::core::dimension2df size ) : IrrlichtNode(modelPath) {
	_size = size;
}

void BillBoardNode::init(){
	IrrlichtNode::init();
}

void BillBoardNode::createNode( ) {
	node = scene->getIrrlichtSceneManager()->addBillboardSceneNode(0, _size, *transform->position);
	
	// Setting materials
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	
	// Setting Texture
	node->setMaterialTexture(0, game->driver->getTexture( this->modelPath ));
}

void BillBoardNode::update(){
	IrrlichtNode::update();
}


BillBoardNode::~BillBoardNode()
{
	IrrlichtNode::~IrrlichtNode();
}
