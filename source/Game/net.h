#ifndef Net_H
#define Net_H

#include <irrlicht/irrlicht.h>
#include <process.h>
#include <sstream>
#include <SFML/Network.hpp>
#include "Engine\Camera.h"
#include "Engine\Camera.h"
#include "Bullet.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
class Net{
	private:
		static int packageid ;
		static int packageidrecieve ;
		static void senderthread(void * var);
		static void revieverthread(void * var);
		static void senderthreadWeapon(void * var);
		static void revieverthreadWeapon(void * var);
	public:
		Net(bool IsWeapon, void * sendervar, void * recievervar);
		Net();
};
#endif