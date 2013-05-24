#ifndef BILLBOARDNODE
#define BILLBOARDNODE

#include "Engine/IrrlichtNode.h"

using namespace irr;
using namespace core;

class BillBoardNode : public IrrlichtNode {
public:
	BillBoardNode(const irr::io::path& modelPath, irr::core::dimension2df size);
	virtual ~BillBoardNode();

	virtual void init();
	virtual void update();

protected:
	irr::core::dimension2df _size;
	virtual void createNode();
};


#endif