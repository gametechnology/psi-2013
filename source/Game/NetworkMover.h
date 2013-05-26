#ifndef NETWORKMOVER
#define NETWORKMOVER

#include <Engine\Network.h>
#include <Engine\NetworkPacket.h>
#include <Engine\INetworkListener.h>
#include "Engine/Component.h"
#include "Engine/Game.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class NetworkMover : public Component, public INetworkListener
{
	public:
		NetworkMover();
		~NetworkMover();
		
		virtual void init();
		virtual void onAdd();
		virtual void update();
		void HandleNetworkMessage(NetworkPacket packet);
};
#endif