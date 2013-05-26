#include <Engine/MeshComponent.h>

MeshComponent::MeshComponent(irr::scene::ISceneManager* smgr) : Component("MeshComponent")
{
	_smgr = smgr;
}

MeshComponent::~MeshComponent()
{
	_smgr->addToDeletionQueue(_node);
	_smgr = NULL;
	_node = NULL;

	delete _mesh;
	_mesh = NULL;	
}

void MeshComponent::createMeshNode(std::string modelPath)
{
	_mesh = _smgr->getMesh(modelPath.c_str());
	
	_node = _smgr->addMeshSceneNode(_mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void MeshComponent::createAnimatedMeshNode(std::string modelPath)
{
	_mesh = _smgr->getMesh(modelPath.c_str());
	
	_node = _smgr->addMeshSceneNode(_mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}