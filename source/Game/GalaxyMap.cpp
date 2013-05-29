#include "GalaxyMap.h"

using namespace irr;
using namespace irr::video;
using namespace irr::core;

GalaxyMap::GalaxyMap(Core* core, irr::f32 width, irr::f32 height, irr::f32 radius) : GameObject()
{
	this->width = width;
	this->height = height;
	this->radius = radius;
	_core = core;
}

void GalaxyMap::init(){
	for(std::list<MapSector*>::iterator it = sectors.begin(); it != sectors.end(); it++)
	{
		addComponent((*it));
	}
	GameObject::init();
}

void GalaxyMap::loadMap()
{

}

void GalaxyMap::saveMap()
{

}

void GalaxyMap::createMap(int sectorCount, int minWormholes, int maxWormholes) {
	MapGenerator mapGenerator = MapGenerator(_core, sectorCount, minWormholes, maxWormholes);
	sectors = *mapGenerator.createNewMap(width, height, radius);
}

void GalaxyMap::createStaticMap() {
	MapGenerator mapGenerator = MapGenerator(_core, 0, 0, 0);
	sectors = *mapGenerator.createStaticMap(width, height, radius);
}

GalaxyMap::~GalaxyMap() {
	for(std::list<MapSector*>::iterator it = sectors.begin(); it != sectors.end(); it++)
	{
		delete (*it);
	}

	sectors.clear();
}

void GalaxyMap::update()
{
	//TODO: uncomment code to make sectors and connections invissible if not visited yet

	ITexture* bgMap = _core->getDriver()->getTexture("../assets/galaxy.jpg");
	_core->getDriver()->draw2DImage(bgMap, rect<s32>(0, 300, (int)width, 300+(int)height), rect<s32>(0, 0, bgMap->getOriginalSize().Width, bgMap->getOriginalSize().Height));
	gui::IGUIFont* font = _core->getDevice()->getGUIEnvironment()->getBuiltInFont();
	rect<s32> imp1(349,15,385,78);

	for(std::list<MapSector*>::iterator it = sectors.begin(); it != sectors.end(); it++)
	{
		for(unsigned int j = 0; j != (*it)->connections.size(); j++) {
			_core->getDriver()->draw2DLine(vector2d<s32>((int)((*it)->getPosition()->X), (int)((*it)->getPosition()->Y)), vector2d<s32>((int)((*it)->connections[j]->getPosition()->X), (int)((*it)->connections[j]->getPosition()->Y)));
		}
		font->draw(irr::core::stringw((*it)->name.c_str()), rect<s32>((int)((*it)->getPosition()->X), (int)((*it)->getPosition()->Y - (1.5f*radius)), 300, 50), SColor(255,255,255,255));
	}

	Composite::update();
}