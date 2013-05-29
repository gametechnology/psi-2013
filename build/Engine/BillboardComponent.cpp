#include <Engine\BillboardComponent.h>

BillboardComponent::BillboardComponent(irr::scene::ISceneManager* smgr, irr::core::vector3df position, irr::core::dimension2df size) : Component("BillboardNode")
{
	_size = size;
	createBillboardNode(position);
}

BillboardComponent::~BillboardComponent()
{
	_smgr->addToDeletionQueue(_node);
	_node = NULL;
}

void BillboardComponent::setTexture(irr::video::IVideoDriver* driver, std::string texturePath)
{
	_node->setMaterialTexture(0, driver->getTexture(texturePath.c_str()));
}

void BillboardComponent::createBillboardNode(irr::core::vector3df position) {
	_node = _smgr->addBillboardSceneNode(0, _size, position);
	
	// Setting materials
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
	_node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);	
}

irr::core::vector3df* BillboardComponent::getPosition()
{
	return &_node->getAbsolutePosition();
}