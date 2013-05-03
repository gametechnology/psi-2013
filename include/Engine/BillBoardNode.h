#ifndef BILLBOARDNODE
#define BILLBOARDNODE

#include "Engine/IrrlichtNode.h"

using namespace irr;
using namespace core;

class BillBoardNode : public IrrlichtNode {
public:
	BillBoardNode(const irr::io::path& modelPath,irr::core::dimension2df size,irr::core::vector3df position,irr::core::vector3df rotation);
	virtual ~BillBoardNode();
	
	void onAdd();
	void createNode();

private:
	irr::core::dimension2df _size;
	irr::core::vector3df _position;
	irr::core::vector3df _rotation;
};


#endif