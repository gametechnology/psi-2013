#ifndef IRRLICHTNODE
#define IRRLICHTNODE

#include "Engine\Component.h"
#include "Engine\Entity.h"

class IrrlichtNode : public Component {
public:
	IrrlichtNode(std::string modelPath);
	virtual IrrlichtNode~();

	void update();
private:
	irr::scene::ISceneNode* node;
	void createNode(std::string modelPath);
}

#endif