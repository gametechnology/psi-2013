#include "CubeNode.h"
#include <Engine\Game.h>

CubeNode::CubeNode(irr::f32 size = 10.0F,irr::core::vector3df position = irr::core::vector3df(0,0,0),irr::core::vector3df rotation = irr::core::vector3df(0,0,0), const irr::io::path& modelPath) : IrrlichtNode(modelPath) {
	_size = size;
	_position = position;
	_rotation = rotation;
}

void CubeNode::onAdd() {
}
void CubeNode::createNode() {
	node = scene->getIrrlichtSceneManager()->addCubeSceneNode(_size, 0, -1,
		_position,
		_rotation
	);
		
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
	node->setMaterialTexture(0, game->driver->getTexture(this->modelPath));
}


CubeNode::~CubeNode()
{
	IrrlichtNode::~IrrlichtNode();
}
