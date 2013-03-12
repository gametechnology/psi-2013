#include "Play.h"
#include "irrlicht.h"
#include "Game.h"
#include "Composite.h"


Play::Play()
{
	irr::scene::IMesh* mesh = Game::scenes->top()->smgr->getMesh("sydney.md2");

	// Create entity
	Entity* myModel = new Entity();
	myModel->irrNode =  Game::scenes->top()->smgr->addMeshSceneNode( mesh );
	Game::scenes->top()->AddComponent(myModel);
}


Play::~Play()
{
	delete myModel;
}
