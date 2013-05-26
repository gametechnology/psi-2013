#include "WormHole.h"
#include "Engine/Game.h"

WormHole::WormHole( unsigned int id ) : BillBoardNode("../assets/Textures/Wormholes/WormHole.png", irr::core::dimension2df (80,100) ) {
	// Setting id and position
	this->id = id;
}

void WormHole::init() {
	BillBoardNode::init();
}

void WormHole::handleMessage(unsigned int message, void* data) {
	delete data;
}

WormHole::~WormHole() {
}
