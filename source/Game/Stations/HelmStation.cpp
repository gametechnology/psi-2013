#include "HelmStation.h"

HelmStation :: HelmStation(Ship *ship) : Station( ship )
{
	this->_stationType = ST_HELM;
	this -> setStationDestroyed(false);

}

HelmStation :: ~HelmStation( )
{
	
}

void HelmStation :: DoCameraShake( )
{
	
}
void HelmStation :: update( )
{
	Station::update();
	
	 NetworkPacket packet(SHIP_ACCELERATION);
	 packet << *_ship->transform->acceleration;
	 packet << *_ship->transform->angularAccelaration;
	 packet << *_ship->transform->position;
	 packet << *_ship->transform->rotation;
	 Network::GetInstance()->SendPacketToAllClients(packet, true);

	 
}

void HelmStation :: OnEnabled(){

}

void HelmStation ::OnDisabled(){
}