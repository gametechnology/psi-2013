#ifndef PSI_BILLBOARD_COMPONENT
#define PSI_BILLBOARD_COMPONENT

#include "Component.h"

#include <string>

class BillboardComponent : public Component {
public:
	BillboardComponent(irr::scene::ISceneManager* smgr, irr::core::vector3df position, irr::core::dimension2df size);
	virtual ~BillboardComponent();

	virtual void setTexture(irr::video::IVideoDriver* driver, std::string texturePath);
private:
	irr::scene::ISceneManager* _smgr;
	irr::scene::ISceneNode* _node;

	irr::core::dimension2df _size;

	void createBillboardNode(irr::core::vector3df position);
};


#endif