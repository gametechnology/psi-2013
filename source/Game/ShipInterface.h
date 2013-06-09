#ifndef SHIPINTERFACE_H
#define SHIPINTERFACE_H

#include "Engine/Entity.h"

class ShipInterFace : public Entity
{
public:
	int getTeamId(int teamId);
private:
	int _teamId;
};
#endif