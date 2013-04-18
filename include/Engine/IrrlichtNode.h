#ifndef IRRLICHTNODE
#define IRRLICHTNODE

#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"

class IrrlichtNode : public Component {
public:
	IrrlichtNode(std::string modelPath);
	~IrrlichtNode();

	void update();
private:
	irr::scene::ISceneNode* node;
	void createNode(std::string modelPath);
};

#endif