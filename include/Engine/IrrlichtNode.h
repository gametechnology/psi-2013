#ifndef IRRLICHTNODE
#define IRRLICHTNODE

#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"

class IrrlichtNode : public Component {
public:
	IrrlichtNode(irr::io::path* modelPath);
	~IrrlichtNode();

	void init();
	void update();
private:
	irr::io::path* modelPath;
	irr::scene::ISceneNode* node;
	void createNode();
};

#endif