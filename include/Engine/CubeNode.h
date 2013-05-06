#ifndef CUBENODE
#define CUBENODE

#include "Engine/IrrlichtNode.h"

using namespace irr;
using namespace core;

class CubeNode : public IrrlichtNode {
public:
	CubeNode(const irr::io::path& modelPath, irr::f32 size,irr::core::vector3df position,irr::core::vector3df rotation);
	virtual ~CubeNode();
	
	void onAdd();
	void createNode();

private:
	float _size;
	irr::core::vector3df _position;
	irr::core::vector3df _rotation;
};


#endif