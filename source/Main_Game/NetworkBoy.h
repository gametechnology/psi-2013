#include <irrlicht.h>
#include <enet/enet.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifndef NETWORKBOY_H
#define NETWORKBOY_H

class NetworkBoy {
    public:
		NetworkBoy();
		~NetworkBoy();
		void connect(const char* ipString);
		void setupServer();
		void flush();
		void receivePackets();

		unsigned short port;
    private:

		ENetHost* host;
		ENetPeer* serverPeer;

		bool isServer;
		ENetAddress serverAddress;
};
#endif