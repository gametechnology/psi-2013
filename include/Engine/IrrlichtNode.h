#ifndef IRRLICHTNODE
#define IRRLICHTNODE

#include "Engine\Component.h"
#include "Engine\Entity.h"

class IrrlichtNode : public Component {
public:
	void update();
private:
	irr::scene::ISceneNode node;
}

#endif