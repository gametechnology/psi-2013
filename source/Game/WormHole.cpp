#include "WormHole.h"
#include "Engine/Game.h"

WormHole::WormHole( unsigned int id ) : BillBoardNode("../assets/Textures/Wormholes/WormHole.png", _size, _position, _rotation ) {
	// Setting id and position
	this->id = id;
	_size = irr::core::dimension2df(80,100);
	_position = irr::core::vector3df(0,0,0);
	_rotation = irr::core::vector3df(0,0,0);
}

void WormHole::onAdd() {
	createNode();
}

void WormHole::handleMessage(unsigned int message, void* data) {
	delete data;
}

WormHole::~WormHole() {
	//_wormhole->remove();
	//delete _wormhole;
	BillBoardNode::~BillBoardNode();
}
