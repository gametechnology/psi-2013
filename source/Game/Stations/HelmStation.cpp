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
	
	 NetworkPacket packet(SHIP_ACCELERATION, true);
	 packet << *_ship->transform->acceleration;
	 packet << *_ship->transform->angularAccelaration;
	 packet << *_ship->transform->position;
	 packet << *_ship->transform->rotation;
	 
	 if(Network::GetInstance()->IsServer())
		Network::GetInstance()->SendServerPacket(packet, true);
	else
		Network::GetInstance()->SendPacket(packet, true);

	 
}

void HelmStation :: OnEnabled(){

}

void HelmStation ::OnDisabled(){
}