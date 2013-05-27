#ifndef PSI_MESH_COMPONENT
#define PSI_MESH_COMPONENT

#include "Component.h"
#include <string>

class MeshComponent : public Component
{
public:
	MeshComponent(irr::scene::ISceneManager*);
	~MeshComponent();

	void createMeshNode(std::string modelPath);
	void createAnimatedMeshNode(std::string modelPath);

	virtual void update(irr::core::vector3df* position, irr::core::vector3df* rotation);
protected:
private:
	irr::scene::ISceneManager* _smgr;
	irr::scene::ISceneNode* _node;

	irr::scene::IMesh* _mesh;
};

#endif