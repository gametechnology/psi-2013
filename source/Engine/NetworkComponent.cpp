#include "Engine\NetworkComponent.h"
#include "Engine\Component.h"
#include "Engine\Composite.h"


NetworkComponent::NetworkComponent() : Component(NULL) {
	
}

void NetworkComponent::update() {
	int* i = integers.front();
	(*i)++;
}

NetworkComponent::~NetworkComponent() {

}