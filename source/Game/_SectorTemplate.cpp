#include "SectorTemplate.h"
#include "Messages.h"

SectorTemplate::SectorTemplate(Composite* parent, const io::path & skyBoxTexture, float boundry) : Entity(parent) {
	
}

void SectorTemplate::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case DAMAGE: /* Do something */;
	}
	delete data;
}

SectorTemplate::~SectorTemplate() {
	Entity::~Entity();
}
