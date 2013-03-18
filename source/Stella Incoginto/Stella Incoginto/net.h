#ifndef Net_H
#define Net_H
#include "stdafx.h"


#include <process.h>
#include <sstream>
#include "client.h"
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;



#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Net{
	public:
		static BOOLEAN isServer;
		static std::string serverip;
		static BOOLEAN isrunning;
		static list<Client> clientlist;
		static list<Client> copyclientlist;
		static Client mypc;
		static int lastpackageidrecieved;
		// 0 = connecting, 1 = inlobby, 2 = loading 3 = ingame
		static int stagegame;
		static void senderthread(void * var);
		static void recieverthread(void * var);
		static Client * GetClientByIp(std::string);
	public:
		Net();		
		Net(std::string);
		void StartGame();
		
			
};
#endif