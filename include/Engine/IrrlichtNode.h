#ifndef IRRLICHTNODE
#define IRRLICHTNODE

#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"

class IrrlichtNode : public Entity {
public:
	IrrlichtNode(const irr::io::path& modelPath);
	virtual ~IrrlichtNode();

	virtual void init();
	virtual void update();

	virtual void setVisible(bool isVisible);
	
protected:
	irr::io::path modelPath;
	irr::scene::ISceneNode* node;
	virtual void createNode();

};

#endif