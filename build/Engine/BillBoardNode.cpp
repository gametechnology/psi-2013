#include "Engine\BillBoardNode.h"
#include <Engine\Game.h>

BillBoardNode::BillBoardNode(const irr::io::path& modelPath, irr::core::dimension2df size = irr::core::dimension2df(10,10),irr::core::vector3df position = irr::core::vector3df(0,0,0),irr::core::vector3df rotation = irr::core::vector3df(0,0,0)) : IrrlichtNode(modelPath) {
	_size = size;
	_position = position;
	_rotation = rotation;
}

void BillBoardNode::onAdd() {
}
void BillBoardNode::createNode() {
	node = scene->getIrrlichtSceneManager()->addBillboardSceneNode(0, _size, _position );
	
	// Setting materials
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	
	// Setting Texture
	node->setMaterialTexture(0, game->driver->getTexture( this->modelPath ));
}


BillBoardNode::~BillBoardNode()
{
	IrrlichtNode::~IrrlichtNode();
}
