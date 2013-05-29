#ifndef PSI_BILLBOARD_COMPONENT
#define PSI_BILLBOARD_COMPONENT

#include "Component.h"

#include <string>

class BillboardComponent : public Component {
public:
	BillboardComponent(irr::scene::ISceneManager* smgr, irr::core::vector3df* position, irr::core::dimension2df size);
	virtual ~BillboardComponent();

	virtual void setTexture(irr::video::IVideoDriver* driver, std::string texturePath);

	virtual void handleMessage(unsigned int, void* data = 0) { };

	irr::core::vector3df* getPosition();
private:
	irr::scene::ISceneManager* _smgr;
	irr::scene::ISceneNode* _node;

	irr::core::dimension2df _size;
	irr::core::vector3df _position;

	void createBillboardNode();
};


#endif