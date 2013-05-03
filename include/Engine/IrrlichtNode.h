#ifndef IRRLICHTNODE
#define IRRLICHTNODE

#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"

class IrrlichtNode : public Entity {
public:
	IrrlichtNode(const irr::io::path& modelPath);
	~IrrlichtNode();

	void init();
	void update();
private:
	virtual void createNode();
protected:
	irr::io::path modelPath;
	irr::scene::ISceneNode* node;

};

#endif