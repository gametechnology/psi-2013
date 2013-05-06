#include <Engine\NetworkComponent.h>
#include <Engine\Component.h>
#include <Engine\Composite.h>
#include <Engine\Game.h>


NetworkComponent::NetworkComponent() : Component() {
	
}

void NetworkComponent::update() {
	/*int* i = integers.front();
	(*i)++;
	vectors.front()->X++;
	Game::client->sendPacket("hallo allemaal");*/
}

NetworkComponent::~NetworkComponent() {

}