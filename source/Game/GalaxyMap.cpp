#include "GalaxyMap.h"
#include "Engine/Game.h"
#include "MapGenerator.h"

GalaxyMap::GalaxyMap(irr::f32 width, irr::f32 height, irr::f32 radius) : Entity()
{
	this->width = width;
	this->height = height;
	this->radius = radius;
}

void GalaxyMap::onAdd(){
	for(unsigned int i = 0; i < sectors.size(); i++) {
		addChild(sectors[i]);
	}
	Entity::onAdd();
}

void GalaxyMap::loadMap()
{

}

void GalaxyMap::saveMap()
{

}

void GalaxyMap::createMap(int sectorCount, int minWormholes, int maxWormholes) {
	MapGenerator mapGenerator = MapGenerator(sectorCount, minWormholes, maxWormholes);
	sectors = *mapGenerator.createNewMap(width, height, radius);
}

void GalaxyMap::createStaticMap() {
	MapGenerator mapGenerator = MapGenerator(0,0,0);
	sectors = *mapGenerator.createStaticMap(width, height, radius);
}

GalaxyMap::~GalaxyMap() {
	for(unsigned i =0;i<sectors.size();i++) {
		delete sectors[i];
	}
	sectors.clear();
}

void GalaxyMap::draw()
{
	//TODO: uncomment code to make sectors and connections invissible if not visited yet

	video::ITexture* bgMap = game->driver->getTexture("../assets/galaxy.jpg");
	game->driver->draw2DImage(bgMap, irr::core::rect<s32>(0, 300, (int)width, 300+(int)height), irr::core::rect<s32>(0, 0, bgMap->getOriginalSize().Width, bgMap->getOriginalSize().Height));

	for(unsigned int i = 0; i < sectors.size(); i++) {
		for(unsigned int j = 0; j != sectors[i]->connections.size(); j++) {
			game->driver->draw2DLine(irr::core::vector2d<irr::s32>((int)(sectors[i]->transform->position->X), (int)(sectors[i]->transform->position->Y)), core::vector2d<irr::s32>((int)(sectors[i]->connections[j]->transform->position->X), (int)(sectors[i]->connections[j]->transform->position->Y)));
		}
	}
	
	gui::IGUIFont* font = game->device->getGUIEnvironment()->getBuiltInFont();
	core::rect<s32> imp1(349,15,385,78);
	
	for(unsigned int i = 0; i < sectors.size(); i++) {
		font->draw(irr::core::stringw(sectors[i]->name.c_str()), core::rect<s32>((int)(sectors[i]->transform->position->X), (int)(sectors[i]->transform->position->Y - (1.5f*radius)), 300, 50), video::SColor(255,255,255,255));
	}

	Entity::draw();
}