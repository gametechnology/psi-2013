#include "GalaxyMap.h"
#include "Engine/Game.h"
#include "MapGenerator.h"

GalaxyMap::GalaxyMap(irr::f32 width, irr::f32 height, irr::f32 radius) : Entity()
{
	this->width = width;
	this->height = height;
	this->radius = radius;
	this->visible = false;
}

void GalaxyMap::onAdd(){
	for(unsigned int i = 0; i < sectors.size(); i++) {
		addChild(sectors[i]);
		sectors[i]->transform->position->X += transform->position->X;
		sectors[i]->transform->position->Y += transform->position->Y;
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

GalaxyMap::~GalaxyMap() 
{
	//keep empty
	//Mapsectors will be deleted anyway
}

void GalaxyMap::draw()
{
	if (!visible) return;
	//TODO: uncomment code to make sectors and connections invissible if not visited yet

	video::ITexture* bgMap = game->driver->getTexture("../assets/galaxy.jpg");
	game->driver->draw2DImage(bgMap, irr::core::rect<s32>(
			transform->position->X,
			transform->position->Y,
			transform->position->X + (int)width,
			transform->position->Y + (int)height),
			irr::core::rect<s32>(0, 0, bgMap->getOriginalSize().Width, bgMap->getOriginalSize().Height));

	for(unsigned int i = 0; i < sectors.size(); i++) {
		//if (sectors->at(i)->explored)
		//{
			for(unsigned int j = 0; j != sectors[i]->connections.size(); j++) {
				//if (sectors->at(i)->explored && sectors->at(j)->explored)
				//{
					game->driver->draw2DLine(
						irr::core::vector2d<irr::s32>(
							(int)(sectors[i]->transform->position->X), 
							(int)(sectors[i]->transform->position->Y)
						),
						core::vector2d<irr::s32>(
							(int)(sectors[i]->connections[j]->transform->position->X),
							(int)(sectors[i]->connections[j]->transform->position->Y)
						)
					);
				//}
			}
		//}
	}
	
	gui::IGUIFont* font = game->device->getGUIEnvironment()->getBuiltInFont();
	core::rect<s32> imp1(349,15,385,78);
	
	for(unsigned int i = 0; i < sectors.size(); i++) {
		//if (sectors->at(i)->explored)
		//{
			font->draw(irr::core::stringw(sectors[i]->name.c_str()),
				core::rect<s32>(
					(int)(sectors[i]->transform->position->X),
					(int)(sectors[i]->transform->position->Y - (1.5f*radius)),
					300, 50), video::SColor(255,255,255,255)
				);
		//}
	}

	Entity::draw();
}