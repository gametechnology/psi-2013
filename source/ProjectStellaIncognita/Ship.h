#ifndef STATION_H
#define STATION_H

#include "irrlicht.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Ship
{
	public:
		Ship();
		~Ship();
		vector3df* shipPosition;
		void setShipPosition(vector3df* shipPosition);
		vector3df getShipPosition();
	private:
		vector3df _shipPosition;
};
#endif