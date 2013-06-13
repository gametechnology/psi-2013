#ifndef IRRLICHTNODE
#define IRRLICHTNODE

#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"

class IrrlichtNode : public Entity {
public:
	IrrlichtNode(const irr::io::path& modelPath);
	virtual ~IrrlichtNode();

	void handleMessage(unsigned int message) {};

	virtual void init();
	virtual void update();

	virtual void setVisible(bool isVisible);
	
protected:
	irr::io::path modelPath;
	irr::scene::ISceneNode* node;
	virtual void createNode();

};

#endif