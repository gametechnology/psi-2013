#include "GalaxyMap.h"
#include "Engine/Game.h"

GalaxyMap::GalaxyMap(Composite* parent):Entity()
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
	//TODO: uncomment code to make sectors and connections invissible if not visited yet

	video::ITexture* bgMap = game->driver->getTexture("../assets/galaxy.jpg");
	game->driver->draw2DImage(bgMap, irr::core::rect<s32>(0, 0, (int)widthMap, (int)heightMap), irr::core::rect<s32>(0, 0, bgMap->getOriginalSize().Width, bgMap->getOriginalSize().Height));

	for(std::list<MapSector*>::iterator i = sectors.begin(); i != sectors.end(); ++i)
	{
		//if ((*i)->explored)
		//{
			for(std::list<MapSector*>::iterator j = (*i)->connections.begin(); j != (*i)->connections.end(); ++j)
			{
				//if ((*i)->explored && (*j)->explored)
				//{
					game->driver->draw2DLine(irr::core::vector2d<irr::s32>((int)((*i)->transform->position->X), (int)((*i)->transform->position->Y)), core::vector2d<irr::s32>((int)((*j)->transform->position->X), (int)((*j)->transform->position->Y)));
				//}
			}
		//}
	}
	
	gui::IGUIFont* font = game->device->getGUIEnvironment()->getBuiltInFont();
	core::rect<s32> imp1(349,15,385,78);
	
	for(std::list<MapSector*>::iterator i = sectors.begin(); i != sectors.end(); ++i)
	{
		//if ((*i)->explored)
		//{
			(*i)->draw();
			font->draw(irr::core::stringw((*i)->name.c_str()), core::rect<s32>((int)((*i)->transform->position->X), (int)((*i)->transform->position->Y - (1.5f*radiusSector)), 300, 50), video::SColor(255,255,255,255));
		//}
	}

	Entity::draw();
}