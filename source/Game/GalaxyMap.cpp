#include "GalaxyMap.h"
#include "Engine/Game.h"

GalaxyMap::GalaxyMap(Composite* parent):Entity(parent)
{

}

void GalaxyMap::loadMap()
{

}
void GalaxyMap::saveMap()
{

}

GalaxyMap::~GalaxyMap()
{
	for(std::list<MapSector*>::iterator i = sectors.begin(); i != sectors.end(); ++i)
	{
		delete (*i);
	}
	sectors.clear();
}

void GalaxyMap::draw()
{
	video::ITexture* bgMap = Game::driver->getTexture("../assets/galaxy.jpg");
	Game::driver->draw2DImage(bgMap, rect<s32>(0,0,widthMap,heightMap), rect<s32>(0,0,bgMap->getOriginalSize().Width,bgMap->getOriginalSize().Height));

	for(std::list<MapSector*>::iterator i = sectors.begin(); i != sectors.end(); ++i)
	{
		for(std::list<MapSector*>::iterator j = (*i)->connections.begin(); j != (*i)->connections.end(); ++j)
		{
			Game::driver->draw2DLine(vector2d<irr::s32>((*i)->position.X, (*i)->position.Y), vector2d<irr::s32>((*j)->position.X, (*j)->position.Y));
		}
	}
	
	gui::IGUIFont* font = Game::device->getGUIEnvironment()->getBuiltInFont();
	core::rect<s32> imp1(349,15,385,78);
	
	for(std::list<MapSector*>::iterator i = sectors.begin(); i != sectors.end(); ++i)
	{
		(*i)->draw();
		font->draw(irr::core::stringw((*i)->name.c_str()), core::rect<s32>((*i)->position.X, (*i)->position.Y - (1.5f*radiusSector), 300, 50), video::SColor(255,255,255,255));
	}

	Entity::draw();
}