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

}

void GalaxyMap::draw()
{
	
	video::ITexture* bgMap = Game::driver->getTexture("../assets/galaxy.jpg");
	Game::driver->draw2DImage(bgMap, rect<s32>(0,0,widthMap,heightMap), rect<s32>(0,0,bgMap->getOriginalSize().Width,bgMap->getOriginalSize().Height));

	for(std::list<MapSector*>::iterator i = sectors.begin(); i != sectors.end(); ++i)
	{
		(*i)->draw();
		/*if ((*i)->type == HOME_BLUE)
		{
			Game::driver->draw2DRectangle(SColor(255, 0, 0, 255), rect<s32>((*i)->position.X - radiusSector, (*i)->position.Y - radiusSector, (*i)->position.X + radiusSector, (*i)->position.Y + radiusSector));
		} else if ((*i)->type == HOME_RED)
		{
			Game::driver->draw2DRectangle(SColor(255, 255, 0, 0), rect<s32>((*i)->position.X - radiusSector, (*i)->position.Y - radiusSector, (*i)->position.X + radiusSector, (*i)->position.Y + radiusSector));
		} else
		{
			Game::driver->draw2DRectangle(SColor(255, 255, 255, 255), rect<s32>((*i)->position.X - radiusSector, (*i)->position.Y - radiusSector, (*i)->position.X + radiusSector, (*i)->position.Y + radiusSector));
		}*/
	}
	Entity::draw();
}
